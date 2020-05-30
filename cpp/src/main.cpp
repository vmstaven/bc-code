#include "Dataset.h"
#include <iostream>
#include <fstream>
int main(int argc, char const *argv[])
{


    // Big data //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // gdalinfo for img center

    Dataset toolbox;

    // cv::Mat             img3 = cv::imread("img/data3/mosaic3.tif");
    // std::ifstream       csv1("csv/ds3_tops_big.csv");
    // Dataset             ds1(img3, csv1,"1");
    // // ds1.generateData();
    // ds1.writeImgTops();

    // // dataset 1 - Works
    // cv::Mat             img1 = cv::imread("img/data1/1_img_big.tif");
    // std::ifstream       csv1("csv/ds1_tops_big.csv");
    // Dataset             ds1(img1, csv1,"1");
    // ds1.generateData();
    // ds1.writeImgTops();

    // dataset 2 - Works
    // cv::Mat             img2 = cv::imread("img/data2/2020-02-08_ChT_oblique_Orthomosaic.tif");
    // std::ifstream       csv2("csv/ds2_tops_big.csv");
    // Dataset             ds2(img2, csv2, "2");
    // ds2.generateData();
    // ds2.writeImgTops();

    // dataset 3

    // dataset 3 scaled
    // cv::Mat img3_scaled = cv::imread("img/data3/3_not_so_big_ortho.tif");
    // std::ifstream       csv3_scaled("csv/ds3_tops_big.csv");
    // Dataset             ds3_scaled(img3_scaled, csv3_scaled,"3");
    // ds1.generateData();
    // ds3_scaled.writeImgTops();

    // cv::Mat             img3_1 = cv::imread("img/data3_1/slice-ortho-0-0.tif");
    // std::ifstream       csv3_1("csv/ds3_tops_big_0-0.csv");
    // Dataset             ds3_1(img3_1, csv3_1, "3_1");
    // ds3_1.writeImgTops();
    // ds3_1.generateData();

    // cv::Mat img3_2 = cv::imread("img/data3_2/slice-ortho-0-1.tif");
    // std::ifstream csv3_2("csv/ds3_tops_big_0-1.csv");
    // Dataset ds3_2(img3_2, csv3_2, "3_2");
    // ds3_2.writeImgTops();
    // ds3_2.generateData();

    // cv::Mat img3_3 = cv::imread("img/data3_3/slice-ortho-1-0.tif");
    // std::ifstream csv3_3("csv/ds3_tops_big_1-0.csv");
    // Dataset ds3_3(img3_3, csv3_3, "3_3");
    // ds3_3.writeImgTops();
    // ds3_3.generateData();

    // cv::Mat img3_4 = cv::imread("img/data3_4/slice-ortho-1-1.tif");
    // std::ifstream csv3_4("csv/ds3_tops_big_1-1.csv");
    // Dataset ds3_4(img3_4, csv3_4, "3_4");
    // ds3_4.writeImgTops();
    // ds3_4.generateData();

    // ds3.writeImgTops();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Test area ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // std::ifstream csv12("csv/ds1_tops_big.csv");
    // Dataset ds12(img12, csv12, "12");

    // cv::Mat             img2 = cv::imread("img/data2/2020-02-08_ChT_oblique_Orthomosaic.tif");
    // std::ifstream       csv2("csv/ds2_tops_big.csv");
    // Dataset             ds2(img2, csv2, "2");

    // cv::Mat thr = cv::imread("img/data1/mosaic_pred_thr_resnet34.tif");
    // cv::Mat non_thr = cv::imread("img/data1/mosaic_pred_resnet34.tif");

    /// CUT SMALL PART OF IMG ////////////////////////////////////////////////////////////////////////
    // cv::Mat resnet18 = cv::imread("img/data1/mosaic_pred_resnet18.tif");
    // cv::Mat resnet34 = cv::imread("img/data1/mosaic_pred_resnet34.tif");
    // cv::Mat resnet50 = cv::imread("img/data1/mosaic_pred_resnet50.tif");
    // int x = resnet18.cols/5;
    // int y = resnet18.rows / 5;
    // int width = 700;
    // int height = 700;

    // cv::imwrite("img/data1/res18tile.png", resnet18(cv::Rect(x, y, width, height)));
    // cv::imwrite("img/data1/res34tile.png", resnet34(cv::Rect(x, y, width, height)));
    // cv::imwrite("img/data1/res50tile.png", resnet50(cv::Rect(x, y, width, height)));

    //Write to file results
    cv::Mat             img1 = cv::imread("img/data1/1_img_big.tif");
    std::ifstream       csv1("csv/ds1_tops_big.csv");
    Dataset             ds1(img1, csv1,"1");
    ds1.writeImgTops();

    // cv::Mat img2 = cv::imread("img/data1/1_img_big.tif");
    // std::ifstream csv2("csv/ds1_tops_big.csv");
    // Dataset ds2(img2, csv2, "2");

    // cv::Mat img1 = cv::imread("img/data2/2_img_big.tif");
    // std::ifstream csv1("csv/ds2_tops_big.csv");
    // Dataset ds1(img1, csv1, "1");

    // cv::Mat img2 = cv::imread("img/data2/dataset2cropped.tif");
    // std::ifstream csv2("csv/ds2_tops_big.csv");
    // Dataset ds2(img2, csv2, "2");

    // std::cout << img1.rows << "x" << img1.cols << std::endl;
    // std::cout << img2.rows << "x" << img2.cols << std::endl;

    // std::string resnet50 = "resnet50";
    // std::string resnet34 = "resnet34";
    // std::string resnet18 = "resnet18";
    // std::ofstream result;
    // result.open("img/results.txt");
    // result << "Results(Unet):.\n";
    // result << "Dataset 1 (cropped)      : " + resnet50 + " " + std::to_string(ds1.predict(resnet50)) + "\n";
    // result << "Dataset 1 (cropped)      : " + resnet34 + " " + std::to_string(ds1.predict(resnet34)) + "\n";
    // result << "Dataset 1 (cropped)      : " + resnet18 + " " + std::to_string(ds1.predict(resnet18)) + "\n";
    
    // result << "Dataset 1 (non-cropped)  : " + resnet50 + " " + std:r:to_string(ds2.predict(resnet50)) + "\n";
    // result << "Dataset 1 (non-cropped)  : " + resnet34 + " " + std::to_string(ds2.predict(resnet34)) + "\n";
    // result << "Dataset 1 (non-cropped)  : " + resnet18 + " " + std::to_string(ds2.predict(resnet18)) + "\n";
    
    // result << "Dataset 2 (cropped)      : " + resnet50 + " " + std::to_string(ds3.predict(resnet50)) + "\n";
    // result << "Dataset 2 (cropped)      : " + resnet34 + " " + std::to_string(ds3.predict(resnet34)) + "\n";
    // result << "Dataset 2 (cropped)      : " + resnet18 + " " + std::to_string(ds3.predict(resnet18)) + "\n";
    
    // result << "Dataset 2 (non-cropped)  : " + resnet50 + " " + std::to_string(ds4.predict(resnet50)) + "\n";
    // result << "Dataset 2 (non-cropped)  : " + resnet34 + " " + std::to_string(ds4.predict(resnet34)) + "\n";
    // result << "Dataset 2 (non-cropped)  : " + resnet18 + " " + std::to_string(ds4.predict(resnet18)) + "\n";


    // Count number
    // cv::Mat red_dots = cv::imread("img/data1/red_dots.png", CV_LOAD_IMAGE_GRAYSCALE);
    // double thresh = 230; // Hyper parameter
    // double maxValue = 255;
    // threshold(red_dots, red_dots, thresh, maxValue, cv::THRESH_BINARY);
    // std::vector<std::vector<cv::Point>> contours;
    // cv::findContours(red_dots, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    // cv::cvtColor(red_dots, red_dots, CV_GRAY2BGR);
    // contours.erase(contours.end());

    // for (size_t i = 0; i < contours.size(); i++)
    // {
    //     cv::drawContours(red_dots, std::vector<std::vector<cv::Point>>(1, contours[i]), -1, cv::Scalar(0, 0, 255), 3, 8);
    // }
    // std::cout << contours.size() << std::endl;
    // cv::imshow("w",red_dots);
    // cv::waitKey();

    // cv::Mat blue_dots = cv::imread("img/data1/blue_dots.png", CV_LOAD_IMAGE_GRAYSCALE);
    // threshold(blue_dots, blue_dots, thresh, maxValue, cv::THRESH_BINARY);
    // std::vector<std::vector<cv::Point>> contours2;
    // cv::findContours(blue_dots, contours2, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    // cv::cvtColor(blue_dots, blue_dots, CV_GRAY2BGR);
    // contours2.erase(contours2.end());

    // for (size_t i = 0; i < contours2.size(); i++)
    // {
    //     cv::drawContours(blue_dots, std::vector<std::vector<cv::Point>>(1, contours2[i]), -1, cv::Scalar(0, 0, 255), 3, 8);
    // }
    // std::cout << contours2.size() << std::endl;
    // cv::imshow("w", blue_dots);
    // cv::waitKey();

    return 0;
}
