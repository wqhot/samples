# encoding=utf-8
#has imported a folder
import hiai
import time

class ModelManager(object):
    def __init__(self):
        pass

    '''
    Graph instance is returned on initialization and None on initialization
    '''

    def CreateGraph(self, model,graph_id, model_engine_id):
        #  get the Graph instance
        myGraph = hiai.Graph(hiai.GraphConfig(graph_id = graph_id))
        if myGraph is None:
            print 'get graph failed'
            return None
        with myGraph.as_default():
            model_engine = hiai.Engine(hiai.EngineConfig(engine_name='ModelInferenceEngine', side=hiai.HiaiPythonSide.Device,internal_so_name='/lib64/libhiai_python_device2.7.so',engine_id = model_engine_id))
            if model_engine is None:
                print 'get model_engine failed'
                return None
            else:
                print 'get model_engine ok!'
            with model_engine.as_default():
                if (None == model_engine.inference(input_tensor_list=hiai.NNTensorList(), ai_model=model)):
                    print 'Init model_engine failed '
                    return None
                else:
                    print 'Init model_engine ok!'
        # to create Graph
        if (hiai.HiaiPythonStatust.HIAI_PYTHON_OK == myGraph.create_graph()):
            print 'create graph ok '
            return myGraph
        else:
            print 'create graph failed'
            return None

    '''
    Returns None if the argument fails or if the reasoning fails
    '''

    def Inference(self, graphHandle, inputTensorList):
        if not isinstance(graphHandle, hiai.Graph):
            print "graphHandle is not Graph object"
            return None
        # Model enter tensorList
        resultList = graphHandle.proc(inputTensorList)
        if resultList is None:
            print 'Inference error'
        return resultList
