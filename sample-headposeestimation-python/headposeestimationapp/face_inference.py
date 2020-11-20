# encoding=utf-8


from  ConstManager import *
import ModelManager
import hiai
from hiai.nn_tensor_lib import DataType
import numpy as np
import cv2

'''
Face detection model does not need alignment, input 300x300, image input must be processed into NUMPY format
'''
class FaceInference(object):
    def __init__(self):
        # The user specifies the ID number of the Graph where the face detection inference engine is located
        self.graph_id = 1000
        self.model_engine_id = 100
        # Face frame coordinates based on input images
        self.boxList = []
        # Face images generated by crop on one frame (saved as numpy array)
        self.nparray = []
        # Instantiate the model management class
        self.model = ModelManager.ModelManager()
        self.width = 300
        self.height = 300
        self.M_left = -0.15
        self.M_right = 0.15
        self.M_top = -0.1
        self.M_bottom = 0.25
        # Describe the inference model and initialize the Graph
        self.graph = None
        self._getgraph()

    def __del__(self):
        self.graph.destroy()

    def _getgraph(self):
        # Describe the inference model
        inferenceModel = hiai.AIModelDescription('face_detection', face_detection_model_path)
        # initialize Graph
        self.graph = self.model.CreateGraph(inferenceModel,self.graph_id,self.model_engine_id)
        if self.graph is None:
            print "Init Graph failed"

    '''
1. Define the format of the input Tensor
2. Invoke the inference interface
3. Save the correct results of a frame inference to self.ResultList
4. Determine if the inference was successful based on the return values True and False
    '''

    def Inference(self,input_image):
        if isinstance(input_image,np.ndarray) is None:
            return False
        h,w,c = input_image.shape
        resized_image = cv2.resize(input_image,(self.width,self.height))
        inputImageTensor = hiai.NNTensor(resized_image)
        nntensorList = hiai.NNTensorList(inputImageTensor)
        # Empty the face data deduced from the previous frame
        del(self.boxList[:])
        del(self.nparray[:])
        # Invoke the reasoning interface
        resultList = self.model.Inference(self.graph, nntensorList)
        # Save the result of the inference to a temporary list
        # Select valid face coordinates from the temporary list and save them in self.ResultList
        # Face generated from the original image with crop (data type numpy array), save to self.nparray in a list
        if resultList is not None:
            for i in range(200):
                if (resultList[0][i][0][0][2] > 0.8 and resultList[0][i][0][0][2] <= 1.0):
                    if (resultList[0][i][0][0][3] < 0):
                        resultList[0][i][0][0][3] = 0
                    if (resultList[0][i][0][0][4] < 0):
                        resultList[0][i][0][0][4] = 0
                    rect_width = resultList[0][i][0][0][5] - resultList[0][i][0][0][3]
                    rect_height = resultList[0][i][0][0][6] - resultList[0][i][0][0][4]
                    if (resultList[0][i][0][0][3] != 0 and abs(self.M_left * rect_width) <= resultList[0][i][0][0][3]):
                        resultList[0][i][0][0][3] = resultList[0][i][0][0][3] + self.M_left * rect_width
                    if (resultList[0][i][0][0][4] != 0 and abs(self.M_top * rect_height) <= resultList[0][i][0][0][4]):
                        resultList[0][i][0][0][4] = resultList[0][i][0][0][4] + self.M_top * rect_height
                    resultList[0][i][0][0][5] = resultList[0][i][0][0][5] + self.M_right * rect_width
                    resultList[0][i][0][0][6] = resultList[0][i][0][0][6] + self.M_bottom * rect_height
                    # Coordinates of the face box
                    self.boxList.append([resultList[0][i][0][0][3]*w, resultList[0][i][0][0][4]*h,
                                            resultList[0][i][0][0][5]*w, resultList[0][i][0][0][6]*h])
                    self.nparray.append(input_image[int(self.boxList[i][1]):int(self.boxList[i][3]),int(self.boxList[i][0]):int(self.boxList[i][2])])
                else:
                    break
        else:
            print ('not inference face in this frame.')
            return False
        return True













