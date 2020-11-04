#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#encoding:utf-8
import platform as plat
import sys
import io

class ModelLanguage(): # Speech model class
	def __init__(self, modelpath):
		self.modelpath = modelpath
		system_type = plat.system() 
		# Because the file path representation of different systems is not the same, it needs to be determined
		
		self.slash = ''
		if(system_type == 'Windows'):
			self.slash = '\\'
		elif(system_type == 'Linux'):
			self.slash = '/'
		else:
			print('*[Message] Unknown System\n')
			self.slash = '/'
		
		if(self.slash != self.modelpath[-1]): # Add a slash at the end of the directory path
			self.modelpath = self.modelpath + self.slash
		
		pass
		
	def LoadModel(self):
		self.dict_pinyin = self.GetSymbolDict('dict.txt')
		self.model1 = self.GetLanguageModel(self.modelpath + 'language_model1.txt')
		self.model2 = self.GetLanguageModel(self.modelpath + 'language_model2.txt')
		self.pinyin = self.GetPinyin(self.modelpath + 'dic_pinyin.txt')
		model = (self.dict_pinyin, self.model1, self.model2 )
		return model
	
	def SpeechToText(self, list_syllable):
		'''
		A special function for speech recognition

		Realize the conversion from phonetic symbols to final text

		Use panic mode to handle a decoding failure
		'''
		length = len(list_syllable)
		if(length == 0): # The parameters passed in do not contain any pinyin
			return ''
		
		lst_syllable_remain = [] # Stores the remaining pinyin sequences
		str_result = ''

		# Store temporary input pinyin sequence
		tmp_list_syllable = list_syllable

		while(len(tmp_list_syllable) > 0):
			# Carry out pinyin to Chinese characters decoding, storage of temporary results
			tmp_lst_result = self.decode(tmp_list_syllable, 0.0)
			
			if(len(tmp_lst_result) > 0): # There are results, no need to panic
				str_result = str_result + tmp_lst_result[0][0]
				
			while(len(tmp_lst_result) == 0): # No results, began to panic
				# Insert the last pinyin
				lst_syllable_remain.insert(0, tmp_list_syllable[-1])
				# Delete the last pinyin
				tmp_list_syllable = tmp_list_syllable[:-1]
				# Again pinyin to Chinese characters decoding
				tmp_lst_result = self.decode(tmp_list_syllable, 0.0)
				
				if(len(tmp_lst_result) > 0):
					# Add in the results
					str_result = str_result + tmp_lst_result[0][0]
				
			# Make up the rest of the results
			tmp_list_syllable = lst_syllable_remain
			lst_syllable_remain = [] # empty

		
		return str_result
	
	def decode(self,list_syllable, yuzhi = 0.0001):
		'''
		Realize the conversion from pinyin to text
		Based on markov chains
		'''
		#assert self.dic_pinyin == null or self.model1 == null or self.model2 == null
		list_words = []
		
		num_pinyin = len(list_syllable)
		#print('======')
		#print('decode function: list_syllable\n',list_syllable)
		#print(num_pinyin)
		# Start speech decoding
		for i in range(num_pinyin):
			#print(i)
			ls = ''
			if(list_syllable[i] in self.dict_pinyin):
#If this pinyin were in the Hanyu pinyin dictionary
# gets a list of characters under pinyin. Ls contains all the characters corresponding to this pinyin
				ls = self.dict_pinyin[list_syllable[i]]
			else:
				break
			
			
			if(i == 0):
				# The first word does the initial processing
				num_ls = len(ls)
				for j in range(num_ls):
					tuple_word = ['',0.0]
					# Set the initial state value of the Markov model
					# Set the initial probability to 1.0
					tuple_word = [ls[j], 1.0]
					#print(tuple_word)
					# Add to the list of possible sentences
					list_words.append(tuple_word)
				
				#print(list_words)
				continue
			else:
				# Start processing the word immediately after the first word
				list_words_2 = []
				num_ls_word = len(list_words)
				#print('ls_wd: ',list_words)
				for j in range(0, num_ls_word):
					
					num_ls = len(ls)
					for k in range(0, num_ls):
						tuple_word = ['',0.0]
						tuple_word = list(list_words[j]) # Take out every phrase in existence
						#print('tw1: ',tuple_word)
						tuple_word[0] = tuple_word[0] + ls[k] # Try to combine all the words that might correspond to the next sound
						#print('ls[k]  ',ls[k])
						
						tmp_words = tuple_word[0][-2:] # Take out the last two words for calculation
						#print('tmp_words: ',tmp_words,tmp_words in self.model2)
						if(tmp_words in self.model2): # Determine if they're in the restate transition table
							#print(tmp_words,tmp_words in self.model2)
							tuple_word[1] = tuple_word[1] * float(self.model2[tmp_words]) / float(self.model1[tmp_words[-2]])
							#Core! The current probability is multiplied by the transition probability, which is formulated to
							#be the number of occurrences of the n-1st and n-th word divided by the number of occurrences of the n-1st word
							#print(self.model2[tmp_words],self.model1[tmp_words[-2]])
						else:
							tuple_word[1] = 0.0
							continue
						#print('tw2: ',tuple_word)
						#print(tuple_word[1] >= pow(yuzhi, i))
						if(tuple_word[1] >= pow(yuzhi, i)):
							# After greater than the threshold, it is retained, otherwise discarded
							list_words_2.append(tuple_word)
						
				list_words = list_words_2
				#print(list_words,'\n')
		#print(list_words)
		for i in range(0, len(list_words)):
			for j in range(i + 1, len(list_words)):
				if(list_words[i][1] < list_words[j][1]):
					tmp = list_words[i]
					list_words[i] = list_words[j]
					list_words[j] = tmp
		
		return list_words
		
	def GetSymbolDict(self, dictfilename):
		'''
		Read the dictionary file of pinyin Chinese characters
		Returns the read dictionary
		'''
		with io.open(dictfilename, 'r', encoding='utf-8') as f:
			#txt_obj = open(dictfilename, 'r',encoding='UTF-8') # Open the file and read in
			txt_text = f.read()
			f.close()
			txt_lines = txt_text.split('\n') # Text segmentation
			dic_symbol = {} # Initializes the symbol dictionary
			for i in txt_lines:
				list_symbol=[] # Initializes the symbol list
				if(i!=''):
					txt_l=i.split('\t')
					pinyin = txt_l[0]
					for word in txt_l[1]:
						list_symbol.append(word)
				dic_symbol[pinyin] = list_symbol
		
		return dic_symbol
		
	def GetLanguageModel(self, modelLanFilename):
		'''
		Read the file for the language model
		Returns the read model
		'''
		with io.open(modelLanFilename, 'r', encoding='utf-8') as f:
			txt_text = f.read()
			f.close()
			txt_lines = txt_text.split('\n') # Text segmentation

			dic_model = {} # Initializes the symbol dictionary
			for i in txt_lines:
				if(i!=''):
					txt_l=i.split('\t')
					if(len(txt_l) == 1):
						continue
					#print(txt_l)
					dic_model[txt_l[0]] = txt_l[1]

		return dic_model
	
	def GetPinyin(self, filename):
		with io.open(filename, 'r', encoding='utf-8') as f:
			txt_all = f.read()
			f.close()

			txt_lines = txt_all.split('\n')
			dic={}

			for line in txt_lines:
				if(line == ''):
					continue
				pinyin_split = line.split('\t')

				list_pinyin=pinyin_split[0]

				if(list_pinyin not in dic and int(pinyin_split[1]) > 1):
					dic[list_pinyin] = pinyin_split[1]
		return dic




