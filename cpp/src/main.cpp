#include "Dataset.h"

int main(int argc, char const *argv[])
{


    // Big data //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // gdalinfo for img center

    Dataset toolbox;
    toolbox.clearData();

    // dataset 1 - BROKEN
    cv::Mat             img1 = cv::imread("img/data1/1_img_big.tif");
    std::ifstream       csv1("csv/ds1_tops_big.csv");
    Dataset             ds1(img1, csv1,"1");
    ds1.generateData();
    ds1.writeImgTops();

    // dataset 2 - WORKS!
    cv::Mat             img2 = cv::imread("img/data2/2020-02-08_ChT_oblique_Orthomosaic.tif");
    std::ifstream       csv2("csv/ds2_tops_big.csv");
    Dataset             ds2(img2, csv2, "2");
    ds2.generateData();
    ds2.writeImgTops();

    // dataset 3
    cv::Mat             img3_1 = cv::imread("img/data3/slice-ortho-0-0.tif");
    std::ifstream       csv3_1("csv/ds3_tops_big_0-0.csv");
    Dataset             ds3_1(img3_1, csv3_1, "3_1");
    ds3_1.writeImgTops();
    ds3_1.generateData();

    cv::Mat img3_2 = cv::imread("img/data3/slice-ortho-0-1.tif");
    std::ifstream csv3_2("csv/ds3_tops_big_0-1.csv");
    Dataset ds3_2(img3_2, csv3_2, "3_2");
    ds3_2.writeImgTops();
    ds3_2.generateData();

    cv::Mat img3_3 = cv::imread("img/data3/slice-ortho-1-0.tif");
    std::ifstream csv3_3("csv/ds3_tops_big_1-0.csv");
    Dataset ds3_3(img3_3, csv3_3, "3_3");
    ds3_3.writeImgTops();
    ds3_3.generateData();

    cv::Mat img3_4 = cv::imread("img/data3/slice-ortho-1-1.tif");
    std::ifstream csv3_4("csv/ds3_tops_big_1-1.csv");
    Dataset ds3_4(img3_4, csv3_4, "3_4");
    ds3_4.writeImgTops();
    ds3_4.generateData();

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
