#include <opencv2/opencv.hpp>

class Dataset
{
    public:

        // Constructors.
        Dataset();
        Dataset(cv::Mat &img, std::ifstream &csv_file, std::string name, double overlab = 0);

        // Destructors.
        ~Dataset();

        // Methods.
        cv::Mat                     getImgBlank();
        cv::Mat                     getImgTops();
        cv::Mat                     getImgMask();
        std::vector<cv::Point>      getTops();
        std::vector<cv::Mat>        getTilesBlank();
        std::vector<cv::Mat>        getTilesTops();
        std::vector<cv::Mat>        getTilesMasks();

        void                        writeImgMask();
        void                        writeImgBlank();
        void                        writeImgTops();                        

        void                        printDims();
        void                        generateData();
        void                        scaleCsv(std::ifstream &csv_small, cv::Mat &img_big, cv::Mat &img_small, std::string path_to_csv);
        void                        moveCsv(std::ifstream &csv_small, std::string path_to_csv, double x_scale, double y_scale, double x_offset, double y_offset);
        void                        cutImage(cv::Mat &img, int pieces, std::string name);
        void                        fuseData();
        void                        clearData();

        std::pair<cv::Mat,int>      markExtrema(cv::Mat &img);
        cv::Mat                     predict();
        cv::Mat                     predict(cv::Mat);
        std::vector<cv::Mat>        predict(std::vector<cv::Mat> tiles);
        cv::Mat                     stitchingTiles(cv::Mat big_img, std::vector<cv::Mat> tiles);

        std::vector<cv::Mat>        generateTiles(cv::Mat &img, int tile_size = 256); // temp

    private:
        bool                        isDotted(cv::Mat &img, cv::viz::Color color);
        bool                        isRed(cv::Mat &img, cv::Point p);
        bool                        isBlack(cv::Mat &img, cv::Point p);
        bool                        isAllBlack(cv::Mat &img);
        bool                        isGoodData(int dataset, int tile_number);
        bool                        enoughDots(cv::Mat &img, int numDots);

        std::vector<cv::Point>      csv2Points(std::ifstream &csvfile);
        void                        placePoints(cv::Mat &img, std::vector<cv::Point> &pts, cv::viz::Color color);
        void                        printPoints(std::vector<cv::Point> points);

        std::vector<cv::Mat>        generateBetterTiles(cv::Mat &img, double overlab, int tile_size = 256);

        void                        tileDims();

        cv::Mat                     img_tops;
        cv::Mat                     img_blank;
        cv::Mat                     img_mask;
        std::vector<cv::Point>      tops;
        std::vector<cv::Mat>        tiles_tops;
        std::vector<cv::Mat>        tiles_blank;
        std::vector<cv::Mat>        tiles_masks;
        std::string                 name = "0";

};

