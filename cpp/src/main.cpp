#include "Dataset.h"

int main(int argc, char const *argv[])
{

    // Small data //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // std::ifstream       csv1_small("csv/ds1_tops.csv");
        // std::ifstream       csv2_small("csv/ds2_tops.csv");
        // std::ifstream       csv3_small("csv/ds3_tops.csv");

        // cv::Mat             img1_small  = cv::imread("img/mosaic1_scaled.tif");
        // cv::Mat             img2_small  = cv::imread("img/mosaic2_scaled.tif");
        // cv::Mat             img3_small  = cv::imread("img/mosaic3_scaled.tif");

        // Dataset             toolbox1(img1_small,csv1_small,"1_small");
        // Dataset             toolbox2(img2_small,csv2_small,"2_small");
        // Dataset             toolbox3(img3_small,csv3_small,"3_small");

        // toolbox1.writeImgTops();
        // toolbox2.writeImgTops();
        // toolbox3.writeImgTops();
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2                                                  ), 10, cv::Scalar(0, 0, 255), 10, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10                                 + 20        ), 9, cv::Scalar(0, 0, 255), 9, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9                             + 40        ), 8, cv::Scalar(0, 0, 255), 8, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9 + 8                         + 60        ), 7, cv::Scalar(0, 0, 255), 7, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9 + 8 + 7                     + 80        ), 6, cv::Scalar(0, 0, 255), 6, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9 + 8 + 7 + 6                 + 100       ), 5, cv::Scalar(0, 0, 255), 5, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9 + 8 + 7 + 6 + 5             + 120       ), 4, cv::Scalar(0, 0, 255), 4, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9 + 8 + 7 + 6 + 5 + 4         + 140       ), 3, cv::Scalar(0, 0, 255), 3, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 180       ), 1, cv::Scalar(0, 0, 255), 1, 1);
    circle(img2_big, cv::Point(img2_big.cols/2,img2_big.rows/2 + 10 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 + 200   ), 0.5, cv::Scalar(0, 0, 255), 0.5, 1);
    
*/

    // Big data //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // gdalinfo for img center

    Dataset toolbox;

    toolbox.clearData();

    // dataset 1
    cv::Mat             img1 = cv::imread("img/data1/1_img_big.tif");
    std::ifstream       csv1("csv/ds1_tops_big.csv");
    Dataset             ds1(img1, csv1,"1");
    ds1.generateData();
    // ds1.writeImgTops();

    // dataset 2
    // cv::Mat             img2 = cv::imread("img/data2/2020-02-08_ChT_oblique_Orthomosaic.tif");
    // std::ifstream       csv2("csv/ds2_tops_big.csv");
    // Dataset             ds2(img2, csv2, "2");
    // ds2.writeImgTops();
    // ds2.generateData();
    

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
