//Usage: g++ opencvtest.cpp -o opencvtestapp `pkg-config --cflags --libs opencv`
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
//Add CUDA support
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/core/cuda.hpp>

using namespace std;
using namespace cv;
using namespace cv::cuda;

enum Backend 
{
  DNN_BACKEND_DEFAULT = 0,
  DNN_BACKEND_HALIDE,
  DNN_BACKEND_INFERENCE_ENGINE,
  DNN_BACKEND_OPENCV,
  DNN_BACKEND_VKCOM,
  DNN_BACKEND_CUDA,
  DNN_BACKEND_WEBNN
};

enum Target {
  DNN_TARGET_CPU = 0,
  DNN_TARGET_OPENCL,
  DNN_TARGET_OPENCL_FP16,
  DNN_TARGET_MYRIAD,
  DNN_TARGET_VULKAN,
  DNN_TARGET_FPGA,
  DNN_TARGET_CUDA,
  DNN_TARGET_CUDA_FP16,
  DNN_TARGET_HDDL
};

int main()
{

	//std::vector<std::pair<namesBackend,namesTarget>>;

	cout << "########## OPENCV Build Information ##########"<< endl;
	std::cout << cv::getBuildInformation() << std::endl;
	cout << "########## OPENCV===>Avaliable Backend and Target ##########"<< endl;
	for(auto const &vpair : cv::dnn::getAvailableBackends())
	{
		std::cout<<vpair.first<<", "<<vpair.second<<std::endl;
  }
            

	std::cout << "##########OPENCV===>Avaliable CUDA Devices##########"<< endl;
	int cuda_devices_number = cv::cuda::getCudaEnabledDeviceCount();
    if(cuda_devices_number != 0)
    {
       cout << "CUDA Device(s) Number: "<< cuda_devices_number << endl;
       DeviceInfo _deviceInfo;
       bool _isd_evice_compatible = _deviceInfo.isCompatible();
       cout << "CUDA Device(s) Compatible: " << _isd_evice_compatible << endl;    
       cout << "GPU: "<< _deviceInfo.cuda::DeviceInfo::name() << endl;
    }
    else
    {
       cout << "There is no CUDA supported GPU" << endl;       
    }  
    
	return 0;
}



// void switch_to_cuda(cv::dnn::Net &net)
// {
//     try {
//         for(auto const &vpair : cv::dnn::getAvailableBackends()){
//             std::cout<<vpair.first<<", "<<vpair.second<<std::endl;
//             if(vpair.first == cv::dnn::DNN_BACKEND_CUDA && vpair.second == cv::dnn::DNN_TARGET_CUDA){
//                 std::cout<<"can switch to cuda"<<std::endl;
//                 net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
//                 net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
//                 break;
//             }
//         }
//     }catch(std::exception const &ex){
//         net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
//         net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
//         throw std::runtime_error(ex.what());
//     }
// }


// switch(vpair.first)
//     {
//       case DNN_TARGET_CPU:
//       std::cout<<"DNN_TARGET_CPU\n";
//       break;
//       case DNN_TARGET_OPENCL:
//       std::cout<<"DNN_TARGET_OPENCL\n";
//       break;
//       case DNN_TARGET_OPENCL_FP16:
//       std::cout<<"DNN_TARGET_OPENCL_FP16\n";
//       break;
//       case DNN_TARGET_MYRIAD:
//       std::cout<<"DNN_TARGET_MYRIAD\n";
//       break;
//       case DNN_TARGET_VULKAN:
//       std::cout<<"DNN_TARGET_VULKAN\n";
//       break;
//       case DNN_TARGET_FPGA:
//       std::cout<<"DNN_TARGET_FPGA\n";
//       break;
//       case DNN_TARGET_CUDA:
//       std::cout<<"DNN_TARGET_CUDA\n";
//       break;
//       case DNN_TARGET_CUDA_FP16:
//       std::cout<<"DNN_TARGET_CUDA\n";
//       break;
//       case DNN_TARGET_HDDL:
//       std::cout<<"DNN_TARGET_HDDL\n";
//       break;
//       default:
//       break;
//     }

//     switch(vpair.second)
//     {
//       case DNN_BACKEND_DEFAULT:
//       std::cout<<"DNN_BACKEND_DEFAULT\n";
//       break;
//       case DNN_BACKEND_HALIDE:
//       std::cout<<"DNN_BACKEND_HALIDE\n";
//       break;
//       case DNN_BACKEND_INFERENCE_ENGINE:
//       std::cout<<"DNN_BACKEND_INFERENCE_ENGINE\n";
//       break;
//       case DNN_BACKEND_OPENCV:
//       std::cout<<"DNN_BACKEND_OPENCV\n";
//       break;
//       case DNN_BACKEND_VKCOM:
//       std::cout<<"DNN_BACKEND_VKCOM\n";
//       break;
//       case DNN_BACKEND_CUDA:
//       std::cout<<"DNN_BACKEND_CUDA\n";
//       break;
//       case DNN_BACKEND_WEBNN:
//       std::cout<<"DNN_BACKEND_WEBNN\n";
//       break;

//       default:
//       break;
//     }
