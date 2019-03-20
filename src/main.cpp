#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <fstream>

void imgRleDecoding(std::string &rle,cv::Mat &seg,cv::Size size)
{
    std::vector<int> begins,lens;
    
    int flag = true;
    std::string::size_type pos = 0, prev_pos = 0;
    while((pos = rle.find_first_of(' ',pos)) != std::string::npos)
    {
        int num = std::stoi(rle.substr(prev_pos,pos-prev_pos));
        if(flag)
        {
            begins.push_back(num);
            flag = false;
        }
        else
        {
            lens.push_back(num);
            flag = true;
        }
        prev_pos = ++pos;
    }
    lens.push_back(std::stoi(rle.substr(prev_pos,rle.size()-prev_pos)));
    seg = cv::Mat(size,CV_8UC1,cv::Scalar(0));
    unsigned char *data = seg.data;

    for(int i = 0; i<begins.size();++i)
    {
        int start = begins[i];
        for(int s = start ; s < start + lens[i] ; ++s) { data[s] = 255; }
    }
    
    seg = seg.t();
}

void imgRleEncoding(std::string &rle,cv::Mat &seg)
{
    cv::Mat transpos_seg = seg.t();

    int col = transpos_seg.cols;
    rle.clear();
    
    cv::Mat nonzeros;
    cv::findNonZero(transpos_seg, nonzeros);
    int size = 2*nonzeros.rows;
    int *data = (int*)nonzeros.data;
    
    if(!data)
    {
        std::cerr<<"NULL pointer to nonzero mat"<<std::endl;
        return ;
    }
    
    rle += std::to_string(data[1]*col+data[0]) + std::string(" ");
    int x = data[0], y = data[1];
    int len = 1;
    for(int i=2;i<size;i+=2)
    {
        if(abs(data[i]-x)+abs(data[i+1]-y) == 1) { ++len; }
        else
        {
            rle += std::to_string(len) + std::string(" ");
            rle += std::to_string(data[i+1]*col+data[i]) + std::string(" ");
            len = 1;
        }
        x = data[i];
        y = data[i+1];
    }
    rle += std::to_string(len);
}

int main(int argc, const char * argv[]) {
    
    cv::Mat src = cv::imread("./imgs/00a9e2ec9.jpg",cv::IMREAD_COLOR);
    fstream infile;
    infile.open("./ref/RLE.csv",std::ios::in);
    
    if(!infile)
    {
        std::cerr<<"File open error"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::vector<cv::Mat> segs;
    std::string rleinput;
    while(std::getline(infile,rleinput))
    {
        cv::Mat seg;
        imgRleDecoding(rleinput, seg, src.size());
        segs.push_back(seg);
    }
 
    std::string rleoutput;
    imgRleEncoding(rleoutput, segs[0]);
    std::cout<<"RLE input: "<<rleinput<<std::endl;
    std::cout<<"RLE output: "<<rleoutput<<std::endl;
    
    
    cv::imshow("img",src);
    cv::imshow("seg",segs[0]);
    cv::waitKey(0);
    cv::destroyAllWindows();
    
}