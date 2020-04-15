#include "Dataset.h"

// Constructors ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dataset::Dataset() {}

Dataset::Dataset(cv::Mat &img, std::ifstream &csv_file,std::string name)
{
    std::cout << "Processing Dataset node...." << std::endl;
    this->name                  = name;
    this->img_blank             = img.clone();
    this->img_tops              = img.clone();
    this->tops                  = csv2Points(csv_file);

    placePoints(img_tops,tops,cv::Scalar(0,0,255)/*cv::viz::Color::red()*/);

    cv::Mat mask(img.rows, img.cols, 1, cv::viz::Color::black());
    placePoints(mask,tops,cv::viz::Color::white());
    this->img_mask              = mask.clone();

    this->tiles_blank           = generateBetterTiles(img_blank,0.8);
    this->tiles_tops            = generateBetterTiles(img_tops,0.8);
    this->tiles_masks           = generateBetterTiles(img_mask,0.8);
}

// Destructors ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dataset::~Dataset() {}

// Methods ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Returns the image without dots (original image).
cv::Mat Dataset::getImgBlank()
{
    return this->img_blank;
}

// Returns the image with tops on.
cv::Mat Dataset::getImgTops()
{
    return this->img_tops;
}

// Returns the image mask.
cv::Mat Dataset::getImgMask()
{
    return this->img_mask;
}

// Returns a vector containing the points for the tree tops.
std::vector<cv::Point> Dataset::getTops()
{
    return this->tops;
}

// Returns the tiles the original image has been cut into.
std::vector<cv::Mat> Dataset::getTilesBlank()
{
    return this->tiles_blank;
}

// Returns the tiles the tops image has been cut into. 
std::vector<cv::Mat> Dataset::getTilesTops()
{
    return this->tiles_tops;
}

// Returns the tiles of masks.
std::vector<cv::Mat> Dataset::getTilesMasks()
{
    return this->tiles_masks;
}

// Writes the original image to the img folder.
void Dataset::writeImgBlank()
{
    std::string img_name = "img/data" + this->name + "/" + this->name + "_img_blank.tif";
    cv::imwrite(img_name,this->img_blank);
}

// Writes the tops image to the img fodler.
void Dataset::writeImgTops()
{
    std::string img_name = "img/data" + this->name + "/" + this->name + "_img_tops.tif";
    cv::imwrite(img_name, this->img_tops);
}

// Writes the makss image to the img folder.
void Dataset::writeImgMask()
{
    std::string img_name = "img/data" + this->name + "/" + this->name + "_img_mask.tif";
    cv::imwrite(img_name, this->img_mask);
}

// prints the dimensions of the full size image.
void Dataset::printDims()
{
    std::cout << (std::to_string(this->img_blank.rows) + "x" + std::to_string(this->img_blank.cols)) << std::endl;
}

// Generates the image tiles with and without tops on them.
void Dataset::generateData()
{

    int min_of_dots_acceptable = 10;

    std::cout << "Generating data for node " << this->name << "..." << std::endl;
    std::cout << "Dataset " << this->name << " has " << this->tops.size() << " tops..." << std::endl;

    // We now select the images we want and generate .png imges based on that.
    for (int i = 0; i < this->tiles_tops.size(); i++)
    {
        // Check if there are trees on the images and cut away false positives.
        if ( enoughDots(this->tiles_tops[i],min_of_dots_acceptable) )
        {
            // std::cout << "tile " << i << " isn't all black" << std::endl;
            // Generate original image tiles.
            std::string tile_orig_name = std::string("tiles/") + "data" + this->name + "/frames/" + "frame_" + this->name + std::string("_tile_") + std::to_string(i) + ".png";
            cv::imwrite(tile_orig_name, this->tiles_blank[i]);

            // Generate masks for segmentation.
            std::string tile_mask_name = std::string("tiles/") + "data" + this->name + "/masks/" + "mask_" + this->name + std::string("_tile_") + std::to_string(i) + ".png";
            cv::imwrite(tile_mask_name, this->tiles_masks[i]);

            // Generate tops image tiles.
            std::string tile_tops = std::string("tiles/") + "data" + this->name + "/tops/" + "tops_" + this->name + std::string("_tile_") + std::to_string(i) + ".png";
            cv::imwrite(tile_tops, this->tiles_tops[i]);
        }
    }
}

bool Dataset::enoughDots(cv::Mat &img,int numDots)
{
    double numRed = 0.0;

    double num_of_pixels_in_dot = 37.0;

    // Count number of red pixels
    for (size_t i = 0; i < img.rows; i++)
    {
        for (size_t j = 0; j < img.cols; j++)
        {
            if ( isRed(img,cv::Point(j,i)) )
                numRed++;
        }
    }

    if( round(numRed/num_of_pixels_in_dot) < numDots )
        return false;
    
    return true;
}

// Clears all tiles
void Dataset::clearData()
{
    system("rm tiles/data1/frames/*");
    system("rm tiles/data1/masks/*");
    system("rm tiles/data2/frames/*");
    system("rm tiles/data2/masks/*");
    system("rm tiles/data3/frames/*");
    system("rm tiles/data3/masks/*");
    system("rm tiles/data/frames/*");
    system("rm tiles/data/masks/*");
}

void Dataset::cutImage(cv::Mat &img, int pieces, std::string name)
{

    std::cout << "Im handling " << name << " now..." << std::endl;
    std::cout << "Its dimensions is as follows: " << img.rows << "x" << img.cols << std::endl;
    double dims_cut = sqrt(pieces);
    std::string filename_png;
    std::string filename_tif;

    int tile_width = round(img.cols/dims_cut);
    int tile_height = round(img.rows/dims_cut);

    int k = 0;

    std::cout << "filename: " << filename_png << std::endl;
    std::cout << "pieces: " << pieces << std::endl;
    std::cout << "dims_cut: " << dims_cut << std::endl;
    std::cout << "tile width: " << tile_width << std::endl;
    std::cout << "tile height: " << tile_height << std::endl;
    // std::cout << "dims for img " << img.cols << "x" << img.rows << std::endl;

    cv::imwrite("dsm_img.tif",img);

    for (size_t i = 0; i < img.rows; i += tile_height)
    {
        for (size_t j = 0; j < img.cols; j += tile_width)
        {
            filename_png = "img/data" + this->name + "/" + name + "_big_part_" + std::to_string(k) + ".tif";
            cv::Mat tile = img(cv::Rect(j, i, tile_width, tile_height));
            cv::imwrite(filename_png,tile);

            // filename_tif = "img/data" + this->name + "/" + name + "_big_part_" + std::to_string(k) + ".tif";
            // cv::Mat tileTif = cv::imread(filename_png);
            // cv::imwrite(filename_tif,tileTif);

            k++;
        }        
    }
}

// Private

// Generates the image tiles and puts them into an vector.
std::vector<cv::Mat> Dataset::generateTiles(cv::Mat &img, int tile_size)
{

    std::vector<cv::Mat> tiles;

    int width = img.cols;
    int height = img.rows;
    int img_num = 0;

    for (int i = 0; (height - i) >= tile_size; i += tile_size)
    {
        for (int j = 0; (width - j) >= tile_size; j += tile_size)
        {
            cv::Mat tile = img(cv::Rect(j, i, tile_size, tile_size));
            tiles.push_back(tile);
            img_num++;
        }
    }
    return tiles;
}

// Generates the image tiles and puts them into an vector - but in a better way double = Percentage overlab.
std::vector<cv::Mat> Dataset::generateBetterTiles(cv::Mat &img, double overlab, int tile_size)
{
    std::vector<cv::Mat> tiles;

    int width   = img.cols;
    int height  = img.rows;
    int img_num = 0;

    for (int i = 0; (height - i) >= tile_size; i += tile_size * ( 1 - overlab ))
    {
        for (int j = 0; (width - j) >= tile_size; j += tile_size * (1 - overlab))
        {
            cv::Mat tile = img(cv::Rect(j, i, tile_size, tile_size));
            tiles.push_back(tile);
            img_num++;
        }
    }
    return tiles;
}

// Converts csv coordinates to cv::Points
std::vector<cv::Point> Dataset::csv2Points(std::ifstream &csvfile)
{
    std::vector<cv::Point> result;
    std::string line;

    for (std::string line; std::getline(csvfile, line);)
    {
        int j;
        for (j = 0; j < line.length(); j++)
        {
            if (line[j] == ',')
                break;
        }
        int x = std::stoi(line.substr(0, j));
        int y = std::stoi(line.substr(j + 1));
        result.push_back(cv::Point(x, y));
    }

    return result;
}

// Checks if a point is black (for outliers in the dark fields)
bool Dataset::isBlack(cv::Mat &img, cv::Point top)
{
    int B = img.at<cv::Vec3b>(top).val[0];
    int G = img.at<cv::Vec3b>(top).val[1];
    int R = img.at<cv::Vec3b>(top).val[2];

    return (B == 0 && G == 0 && R == 0);
}

// Checks if a point in an image is red.
bool Dataset::isRed(cv::Mat &img, cv::Point p)
{
    if (img.at<cv::Vec3b>(p).val[0] < 100 && img.at<cv::Vec3b>(p).val[1] < 100 && img.at<cv::Vec3b>(p).val[2] > 125)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// This checks if there is a Red dot (marker for tree) on the image.
bool Dataset::isDotted(cv::Mat &img,cv::viz::Color color)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            if (img.at<cv::Vec3b>(cv::Point(i, j)).val[0] == color.val[0] && img.at<cv::Vec3b>(cv::Point(i, j)).val[1] == color.val[1] && img.at<cv::Vec3b>(cv::Point(i, j)).val[2] == color.val[2])
                return true;
        }
    }
    return false;
}

// This prints the points in the vector given.
void Dataset::printPoints(std::vector<cv::Point> points)
{
    for (int i = 0; i < points.size(); i++)
    {
        std::cout << "P" << i << "(" << points[i].x << "," << points[i].y << ")" << std::endl;
    }
}

// Places the points in the vector on the image, the points are marked by a red dot.
void Dataset::placePoints(cv::Mat &img, std::vector<cv::Point> &pts, cv::viz::Color color)
{
    for (int i = 0; i < pts.size(); i++)
    {
        circle(img, pts[i], 2, color, 2, 1); // Orig radius 2 and thickness 2
    }
}

// This scales csv coordinates (Not nessecary anymore!)
void Dataset::scaleCsv(std::ifstream &csv_small, cv::Mat &img_big, cv::Mat &img_small, std::string path_to_csv)
{
        std::string line;
        std::ofstream bigger_csv;
        bigger_csv.open(path_to_csv);

        double scale_cols = 1; //double(double(img_big.cols) / double(img_small.cols));
        double scale_rows = 1; //double(double(img_big.rows) / double(img_small.rows));
        // double scale_rows = scale_cols;
        // double scale_cols = scale_rows;

        int offset_x = 750;//-7356 - 2163; // This offset is in case of a linear shift in coordinates in x and y.
        int offset_y = 0;//-13740 - 3665; // This offset is in case of a linear shift in coordinates in x and y.

        std::cout << "Scaling factors(rows,cols): " << scale_rows << " & " << scale_cols << std::endl;

        for (std::string line; std::getline(csv_small, line);)
        {
            int j;
            for (j = 0; j < line.length(); j++)
            {
                if (line[j] == ',')
                    break;
            }

            // std::cout << double(std::stoi(line.substr(0, j))) * scale_rows << std::endl;
            // std::cout << double(std::stoi(line.substr(j + 1))) * scale_cols << std::endl;

            int x = double(std::stoi(line.substr(0, j))) * scale_cols - offset_x;
            int y = double(std::stoi(line.substr(j + 1))) * scale_rows - offset_y;

            bigger_csv << std::to_string(x) + "," + std::to_string(y) + "\n";
        }
        bigger_csv.close();
}

void Dataset::moveCsv(std::ifstream &csv_small, std::string path_to_csv ,double x_scale, double y_scale, double x_offset, double y_offset)
{
    std::string line;
    std::ofstream bigger_csv;
    bigger_csv.open(path_to_csv);

    for (std::string line; std::getline(csv_small, line);)
    {
        int j;
        for (j = 0; j < line.length(); j++)
        {
            if (line[j] == ',')
                break;
        }

        // std::cout << double(std::stoi(line.substr(0, j))) * scale_rows << std::endl;
        // std::cout << double(std::stoi(line.substr(j + 1))) * scale_cols << std::endl;

        int x = double(std::stoi(line.substr(0, j))) * x_scale - x_offset;
        int y = double(std::stoi(line.substr(j + 1))) * y_scale - y_offset;

        bigger_csv << std::to_string(x) + "," + std::to_string(y) + "\n";
    }
    bigger_csv.close();
}
// OBS! write when tiles can be generated with correctly placed tops.
bool Dataset::isGoodData(int dataset, int tile_number)
{
    return true;
}

// Checks if the image is all black.
bool Dataset::isAllBlack(cv::Mat &img)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            if (isBlack(img, cv::Point(j, i)))
                continue;
            else
                return false;
        }
    }
    return true;
}

// Just some method for quick calculations.
void Dataset::tileDims()
{
    // Calculate tilesize ///////////////////////////////////////////////////////
    constexpr int MAX_NUM_OF_TILES = 74;
    for (double dim = 100; dim < 700; dim += 50)
    {

        std::cout << " Number of tiles: " << double(3161 / dim) << " | "
                  << "dimensions: " << dim << "x" << dim << std::endl;
        // dimensions wanted: 350x350 , num of tiles wanted ~21 tiles. (width)
    }
    std::cout << "Height dimensions: " << double(double(3577) / double(350)) << std::endl;
    // 39 tiles in height of dimensions 350x350
}