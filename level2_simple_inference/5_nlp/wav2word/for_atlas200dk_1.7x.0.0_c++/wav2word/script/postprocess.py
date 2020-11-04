# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

# coding=utf-8

#pcm_path = r'speech_voice/01.pcm'
import os
import numpy as np
import wave
from scipy.fftpack import fft
from ctc_func import greedy_decode
from get_symbol_list import GetSymbolList
from language_model_func import ModelLanguage

x=np.linspace(0, 400 - 1, 400, dtype = np.int64)
w = 0.54 - 0.46 * np.cos(2 * np.pi * (x) / (400 - 1) ) # Hamming window
AUDIO_FEATURE_LENGTH = 200
outpath = "/mnt/shared/project/NLP/out/"
def pcm2wav(pcm_path):
    # Turn on and read the PCM audio
    pcmfile = open(pcm_path, 'rb')
    pcmdata = pcmfile.read()
    pcmfile.close()

    # Set waV audio parameters
    channels = 2
    bits = 16
    sample_rate = 16000

    # Defines the generation path and name of WAV audio
    wave_path_front = pcm_path[:-4]
    wave_path = wave_path_front + '.wav'

    # Create a WAV audio file
    wavfile = wave.open(wave_path, 'wb')

    wavfile.setnchannels(channels)
    wavfile.setsampwidth(bits // 8)
    wavfile.setframerate(sample_rate)

    # Write WAV audio data
    wavfile.writeframes(pcmdata)

    wavfile.close()

    return wave_path
def read_wav_data(filename):
    wav=wave.open(filename,"rb")
    num_frame=wav.getnframes()
    num_channel=wav.getnchannels()
    framerate=wav.getframerate()
    num_sample_width=wav.getsampwidth()
    str_data=wav.readframes(num_frame)
    wav.close()
    wave_data=np.frombuffer(str_data,dtype=np.short)
    wave_data.shape=-1,num_channel
    wave_data=wave_data.T
    #print("ks",framerate)
    return wave_data,framerate

def GetFrequencyFeature3(wavsignal, fs):
    if (16000 != fs):
        raise ValueError(
            '[Error] ASRT currently only supports wav audio files with a sampling rate of 16000 Hz, but this audio is ' + str(
                fs) + ' Hz. ')

    # Wav waveform plus time window and time shift 10ms
    time_window = 25  # Unit of ms
    window_length = fs / 1000 * time_window  # The formulas for calculating window length are all fixed values of 400 at present
    #print window_length
    wav_arr = np.array(wavsignal)
    # wav_length = len(wavsignal[0])
    wav_length = wav_arr.shape[1]
    range0_end = int(float(len(wavsignal[0])) / fs * 1000 - time_window) // 10  # Calculate where the loop ends, which is the final number of Windows 978
    data_input = np.zeros((range0_end, 200), dtype=np.float)  # Used to store the final frequency characteristic data
    data_line = np.zeros((1, 400), dtype=np.float)
    for i in range(0, range0_end):
        p_start = i * 160
        p_end = p_start + 400
        data_line = wav_arr[0, p_start:p_end]
        data_line = data_line * w  # Add window
        data_line = np.abs(fft(data_line)) / wav_length
        data_input[i] = data_line[0:200]  # The value set to 400 divided by 2 (i.e. 200) is half of the data because it is symmetric

    # print(data_input.shape)
    data_input = np.log(data_input + 1)
    return data_input

def RecognizeSpeech(wavsignal, fs):
    data_input = GetFrequencyFeature3(wavsignal, fs)
    input_length = len(data_input)  #978
    input_length = input_length // 8  #122

    data_input = np.array(data_input, dtype=np.float32)

    data_input = data_input.reshape(data_input.shape[0], data_input.shape[1], 1)  #978,200,1
    batch_size = 1
    in_len = np.zeros((batch_size), dtype = np.int32)

    in_len[0] = input_length

    x_in = np.zeros((batch_size, 1600, AUDIO_FEATURE_LENGTH, 1), dtype=np.float32) #1,1600,200,1

    for i in range(batch_size):
        x_in[i, 0:len(data_input)] = data_input

    return x_in, in_len

def RecognizeSpeech_FromFile(filename):
    '''
    The final function to do speech recognition, recognition of the specified filename speech
    '''

    wavsignal,fs1 = read_wav_data(filename)  # Recognize speech features fs1=16000 len(wavsignal[0])=157000
    r, in_len = RecognizeSpeech(wavsignal, fs1)
    return r, in_len
def GetDataSet(speech_voice_path):
    """ Read audio data in PCM format """

    # Convert PCM data to WAV
    #wave_path = L.pcm2wav(speech_voice_path) 

    # Read waV audio features
    features, in_len = RecognizeSpeech_FromFile(speech_voice_path)     

    # Convert WAV audio features into model input vectors
    out_file_name = speech_voice_path.split('.')[0]
    out_filename = out_file_name+'.bin'
    writer = open(out_filename,"wb")
    writer.write(features)
    return in_len

def GetDataSet2(speech_voice_path):
    """ Directly read audio data in WAV format """

    features, in_len = RecognizeSpeech_FromFile(speech_voice_path) #1,1600,200,1  in_len=122 All zero matrices
    features1=np.reshape(features,[1,1600,200,1])

    features1=np.transpose(features1,(0,3,1,2)).copy()
    np.save('features1',features1)
    
    writer = open("features1.bin","wb")
    writer.write(features)
    return  in_len

def SpeechPostProcess(resultList, in_len): 

    # Convert a three-dimensional matrix to a two-dimensional one
    dets = np.reshape(resultList, (200,1424))

    # Converts the identification result to a pinyin sequence
    rr, ret1 = greedy_decode(dets)

    # Remove the blank from the pinyin sequence
    for i in range(len(ret1)):
        if i % 2 == 0:
            try:
                ret1.remove(1423)
            except:
                pass

    list_symbol_dic = GetSymbolList()

    r_str = []
    for i in ret1:
        r_str.append(list_symbol_dic[i])

    #print "Pinyin sequence identification results：" + str(r_str)
    string_pinyin = str(r_str)

    ml = ModelLanguage('language_model')

    ml.LoadModel()

    str_pinyin = r_str

    r = ml.SpeechToText(str_pinyin)

    print(r)

    # Save the results of speech recognition
    with open('results/asr_results.txt','a+b') as f:
        data = string_pinyin[1:-1] + '-' + r + '\n'
        #print(data)
        data=data.encode()
        f.write(data)
        f.close()

    return r, str_pinyin

if __name__ == "__main__":

    current_path = os.path.abspath(__file__)    # Gets the parent directory of the current file
    voicefiles = os.listdir(r'../data/') # get wav
    for voice_name in voicefiles:
        if not voice_name.endswith("wav"):
            continue
        print("start to process image {}....".format(voice_name))
        inputname = os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep + "../data/"),voice_name)
        in_len = GetDataSet(inputname)
        print(outpath)
        outputname = os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep + "../out/"),"output2_0.bin")
        resultList = np.fromfile(outputname,np.float32)
        # Determine if the model inference is successful
    	#if resultList is None:
            #print("Inference failed")
        resultList=np.reshape(resultList,(200,1424))
        # Post-process the results

        txt, pinyin = SpeechPostProcess(resultList,in_len)
        print('pinyin： ' + str(pinyin))
        print('txt： ' + str(txt))
