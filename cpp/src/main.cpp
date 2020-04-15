#include "Dataset.h"

int main(int argc, char const *argv[])
{


    // Big data //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // gdalinfo for img center

    Dataset toolbox;
    toolbox.clearData();

    // dataset 1
    cv::Mat             img1 = cv::imread("img/data1/1_img_big.tif");
    std::ifstream       csv1("csv/ds1_tops_big.csv");
    Dataset             ds1(img1, csv1,"1");
    ds1.generateData();

    // dataset 2
    cv::Mat             img2 = cv::imread("img/data2/2020-02-08_ChT_oblique_Orthomosaic.tif");
    std::ifstream       csv2("csv/ds2_tops_big.csv");
    Dataset             ds2(img2, csv2, "2");
    ds2.generateData();
    

    // dataset 3
    // cv::Mat             img3 = cv::imread("img/data3/mosaic3.tif");
    // std::ifstream       csv3("csv/ds3_tops_big.csv");
    // Dataset             ds3(img3, csv3, "3");
    // ds3.writeImgTops();
    // ds3.generateData();

    // ds3.writeImgTops();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Test area ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // cv::Mat chris = cv::imread("img/test/chris.jpg");
    // Dataset toolbox;
    // std::vector<cv::Mat> c = toolbox.generateBetterTiles(chris,0.8);

    // std::cout << c.size() << std::endl;

    // for (size_t i = 0; i < c.size(); i++)
    // {
    //     std::string tilename = "img/test/tiles/" + std::to_string(i) + ".jpg";
    //     cv::imwrite(tilename,c[i]);
    // }
    

    return 0;
}
