clc; clear; close all;
% IF TRUE, THIS TERMINATES THE PROGRAM AFTER FIRST VERIFICATION OF THE FILTER VALUES
syms fiddle_with_thresholds; fiddle_with_thresholds=0

% IF TRUE, USE POLYGON CROPPING
syms do_poly_crop; do_poly_crop=0

syms use_block_proccesing; use_block_proccesing=1
block_size = [500 500]; %1000
border_size = [50 50]; %100
block_info= [block_size ; border_size];

% tophat_structure_element_size=15; %15 DEFAULT VALUE, THIS IS CHANGED IN THE TOPHAT SECTION, AND NOT HERE
% opening_structure_element_size=7; %7 DEFAULT VALUE, THIS IS CHANGED IN THE OPENING SECTION, AND NOT HERE


height_index_span=0.25; % the height index span in meters

syms org_image_print; org_image_print=0
syms height_cropped_DSM_print; height_cropped_DSM_print=0
syms top_hat_image_print; top_hat_image_print=0
syms top_hat_opened_image_print; top_hat_opened_image_print=0
syms regional_maxima_image_print; regional_maxima_image_print=0
syms verification_filter_image_print; verification_filter_image_print=0;
syms super_image_print; super_image_print=1
syms super_image_color_print; super_image_color_print=0
syms verification_image_print; verification_image_print=1

clc
% SELECT WHICH DATASET TO LOAD
dataset_number  = 1
part_of_3       = 0

th_1 = 18; opn_1 = 9;
th_2 = 18; opn_2 = 9;
th_3 = 24; opn_3 = 12;


switch dataset_number
    case 1
        file_name='data1/1_big_big_norm_dsm.tif'; % first dataset
        ortho_file_name='data1/mosaic1.tif';
        ortho_image = imread(ortho_file_name); % used for verification
        ortho_image_rgb = ortho_image(:,:,1:3);% takes the first three channels

%         file_name='plain_trees.tif'; % 
%         ortho_image = imread(file_name); % 
%         ortho_image_rgb = ortho_image;% 
        
        %__________________________________________________________________________
        %CHANGE THE FILTER VALUES HERE :
        
%         tophat_structure_element_size=15 
%         opening_structure_element_size=7 
        
        tophat_structure_element_size= th_1%12 

        opening_structure_element_size=opn_1%6  
        %__________________________________________________________________________
        
    case 2
        %file_name='normalized_DSM_v2.tif'; % second dataset
        %file_name='TIN_norm_DSM.tif';
        file_name='data2/2_test_big_big_dsm.tif'; % Victor test
        %file_name='dataset_two/new_norm_dsm_20200208.tif';
        %ortho_image = imread('dataset_two/new_scaled_orthomosaic_20200208.tif'); % used for verification
        ortho_filen_name ='data2/2020-02-08_ChT_oblique_Orthomosaic.tif'; %Victor test
        ortho_image_largest=load_largest_tif_layer(ortho_filen_name, org_image_print);
        
        ortho_image_rgb = ortho_image_largest(:,:,1:3);% takes the first three channels
        
        %__________________________________________________________________________
        %CHANGE THE FILTER VALUES HERE :
%         tophat_structure_element_size=4 %5 
% 
%         opening_structure_element_size=2 %2 
        
        tophat_structure_element_size=th_2 %5 

        opening_structure_element_size=opn_2 %2 
        %__________________________________________________________________________
        
    case 3
        switch part_of_3
            case 1
                file_name='data3/slice-dsm-0-0.tif';
                ortho_image = imread('data3/slice-ortho-0-0.tif');
            case 2
                file_name='data3/slice-dsm-0-1.tif';
                ortho_image = imread('data3/slice-ortho-0-1.tif');
            case 3
                file_name='data3/slice-dsm-1-0.tif';
                ortho_image = imread('data3/slice-ortho-1-0.tif');
            case 4
                file_name='data3/slice-dsm-1-1.tif';
                ortho_image = imread('data3/slice-ortho-1-1.tif');
            otherwise
                file_name='data3/3_not_so_big_norm_dsm_v2.tif';
                ortho_image = imread('data3/3_not_so_big_ortho_v2.tif');
        end
        
        %file_name='data3/3_big_big_norm_dsm.tif';
        %ortho_image = imread('data3/mosaic3.tif');
        %ortho_image = imread('20200305_scaled_ortho.tif'); % used for verification
        ortho_image_rgb = ortho_image(:,:,1:3);% takes the first three channels
        
        %__________________________________________________________________________
        %CHANGE THE FILTER VALUES HERE :
        tophat_structure_element_size=th_3 %5 

        opening_structure_element_size=opn_3 %2 
        %__________________________________________________________________________
    otherwise
        disp('wrong value  entered')
end

disp('Setup completed')
disp('___________________________________________________________________________')


%% Load largest layer

org_image=load_largest_tif_layer(file_name, org_image_print);
disp('min & max values:')
disp(get_min_max(org_image))

disp('Image loaded ')
disp('___________________________________________________________________________')


%% height crop
min_tree_height=0.3; % in meters, all objects lower than this limit is ignored
max_tree_height=3; % in meters, all objects taller than this limit is ignored
% 
% min_tree_height=-50; % in meters, all objects lower than this limit is ignored
% max_tree_height=300; % in meters, all objects taller than this limit is ignored

disp('Height cropped between ')

height_cropped_DSM =height_crop(org_image, min_tree_height, max_tree_height,height_cropped_DSM_print);

disp('___________________________________________________________________________')

%% Tophat filtering


tophat_image = tophat_filtering(org_image, tophat_structure_element_size, top_hat_image_print, use_block_proccesing,block_info);

% tophat_image = tophat_filtering(height_cropped_DSM, tophat_structure_element_size, top_hat_image_print, use_block_proccesing,block_info);
% OBS PÅ HVORDAN TOPHAT AFHÆNGER AF HEIGHT CROP

disp('___________________________________________________________________________')

%% Opening

tophat_opened= opening(tophat_image, opening_structure_element_size, top_hat_opened_image_print, use_block_proccesing,block_info);
disp('___________________________________________________________________________')


%% regional_maxima
disp('regional maxima generated')
regional_maxima_opened=regional_maxima(tophat_opened,regional_maxima_image_print,use_block_proccesing,block_info);
disp('___________________________________________________________________________')
%% Verification of filters
if(verification_filter_image_print)
    
% ortho_image = imread('ortho.tif');
% ortho_image_changed = ortho_image(:,:,1);% takes the first three channels

   

tmp=size(org_image);
% verification_image_filters=org_image;
verification_image_filters=ortho_image_rgb;

   for i =1:tmp(1)
       for j=1:tmp(2)
           if(regional_maxima_opened(i,j))
               verification_image_filters(i,j,1:2) = 255;
           end 
           
       end
   end
   clear tmp;
% verification_image_filters= org_image - tophat_opened;
figure('NumberTitle', 'off', 'Name', 'verification_image_filters')
imshow(verification_image_filters)
end

if(fiddle_with_thresholds)
    return;
end

%% polygon_crop and super image

if(do_poly_crop)
poly_crop_region=polygon_crop(regional_maxima_opened);
super_image=make_super_image(regional_maxima_opened, height_cropped_DSM,poly_crop_region, min_tree_height, max_tree_height, super_image_print);
else
super_image=make_super_image(regional_maxima_opened, height_cropped_DSM,regional_maxima_opened, min_tree_height, max_tree_height, super_image_print);
end

disp('___________________________________________________________________________')

%% Count and color plot approx of heights

count_and_color_plot_approx_of_heights(super_image, super_image_color_print);

disp('___________________________________________________________________________')


%% height indexing

height_data=height_indexing(super_image,height_index_span);

overview_of_heights=height_data.heights_grouped;
xyz_coordinates_of_tree_tops=height_data.xyz_coordinates_of_maximas;  
disp('___________________________________________________________________________')

% Victor changes %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

x_coor = xyz_coordinates_of_tree_tops(:,1);
y_coor = xyz_coordinates_of_tree_tops(:,2);


if (dataset_number == 1)
        % comes from gdalinfo <img>
    center_dsm=[205670.431000000011409,6136825.463399999774992];
    center_ortho=[205670.466943187988363,6136825.354980429634452];
    pixelsize=-0.019999999999942;
    x_offset=vpa((center_dsm(1)-center_ortho(1))/pixelsize);
    y_offset=vpa((center_dsm(2)-center_ortho(2))/pixelsize);
    x_coor = x_coor - x_offset;
    y_coor = y_coor - y_offset;    
    xy_coor = [x_coor y_coor];
    csvwrite('ds1_tops_big.csv',xy_coor);
elseif(dataset_number == 2)
    % comes from gdalinfo <img>
    center_dsm=[205438.500000000000000,6136853.017199999652803];
    center_ortho=[205457.246473931008950,6136853.010721740312874];
    pixelsize=-0.025000000000000;
    x_offset=vpa((center_dsm(1)-center_ortho(1))/pixelsize);
    y_offset=vpa((center_dsm(2)-center_ortho(2))/pixelsize);
    x_coor = x_coor - x_offset;
    y_coor = y_coor - y_offset;
    xy_coor = [x_coor y_coor];
    csvwrite('ds2_tops_big.csv',xy_coor);
else

    %pixel size taken from ortho
    % try with collected image offset.
%     center_dsm=[168124.579999999987194 6193226.279000000096858];
%     center_ortho=[168132.776229660987156,6193222.189310640096664];
%     pixelsize=-0.007999999999966;
    
% PLZ FIX

    switch part_of_3
        
        case 0
%             % dsm
%             Origin = (168124.579999999987194,6193226.279000000096858)
        %     Pixel Size = (0.014999597039476,-0.015000497203290)

%             % ortho
%             Origin = (168132.776199999992969,6193222.189299999736249)
%             Pixel Size = (0.015000090702950,-0.014999184117424)
            
            center_dsm=[168215.778, 6193165.940];
            center_ortho=[168215.464, 6193167.037];
            pixelsize=0.015000090702950;
            x_offset=vpa((center_dsm(1)-center_ortho(1))/pixelsize);
            y_offset=vpa((center_dsm(2)-center_ortho(2))/pixelsize);
            x_coor = x_coor - x_offset;
            y_coor = y_coor - y_offset;
            xy_coor = [x_coor y_coor];
            csvwrite('ds3_tops_big.csv',xy_coor);
        case 1
            center_dsm=[168124.579999999987194 6193226.279000000096858];
            center_ortho=[168132.776229660987156 6193222.189310640096664];
            pixelsize=-0.007999999999966;
            x_offset=vpa((center_dsm(1)-center_ortho(1))/pixelsize);
            y_offset=vpa((center_dsm(2)-center_ortho(2))/pixelsize);
            x_coor = x_coor - x_offset;
            y_coor = y_coor - y_offset;
            xy_coor = [x_coor y_coor];
            csvwrite('ds3_tops_big_0-0.csv',xy_coor);
        case 2
            center_dsm=[168215.773549932026071 6193226.279000000096858];
            center_ortho=[168215.464229660981800 6193222.189310640096664];
            pixelsize=-0.007999999999966;
            x_offset=vpa((center_dsm(1)-center_ortho(1))/pixelsize);
            y_offset=vpa((center_dsm(2)-center_ortho(2))/pixelsize);
            x_coor = x_coor - x_offset;
            y_coor = y_coor - y_offset;
            xy_coor = [x_coor y_coor];
            csvwrite('ds3_tops_big_0-1.csv',xy_coor);
        case 3
            center_dsm=[168124.579999999987194 6193165.943499966524541];
            center_ortho=[168132.776229660987156 6193167.037310640327632];
            pixelsize=-0.007999999999966;
            x_offset=vpa((center_dsm(1)-center_ortho(1))/pixelsize);
            y_offset=vpa((center_dsm(2)-center_ortho(2))/pixelsize);
            x_coor = x_coor - x_offset;
            y_coor = y_coor - y_offset;
            xy_coor = [x_coor y_coor];
            csvwrite('ds3_tops_big_1-0.csv',xy_coor);
        case 4
            center_dsm=[168215.773549932026071 6193165.943499966524541];
            center_ortho=[168215.464229660981800 6193167.037310640327632];
            pixelsize=-0.007999999999966;
            x_offset=vpa((center_dsm(1)-center_ortho(1))/pixelsize);
            y_offset=vpa((center_dsm(2)-center_ortho(2))/pixelsize);
            x_coor = x_coor - x_offset;
            y_coor = y_coor - y_offset;
            xy_coor = [x_coor y_coor];
            csvwrite('ds3_tops_big_1-1.csv',xy_coor);
    end
    
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%% Verification
if(verification_image_print)
    
% ortho_image = imread('ortho.tif');
% ortho_image_changed = ortho_image(:,:,1);% takes the first three channels
    

tmp=size(org_image);

verification_image=ortho_image_rgb;

   for i =1:tmp(1)
       for j=1:tmp(2)
           if(super_image(i,j))
               verification_image(i,j,1:2) = 255;
           end 
           
       end
   end
   clear tmp;
% verification_image_filters= org_image - tophat_opened;
% figure('NumberTitle', 'off', 'Name', 'verification_image_filters')
% imshow(verification_image_filters)
% 
% verification_image= ortho_image_rgb - super_image;
figure('NumberTitle', 'off', 'Name', 'verification_image')
imshow(verification_image)
end
disp('___________________________________________________________________________')

%__________________________________________________________________________
%__________________________________________________________________________
%% FUNCTIONS

function f = get_min_max(A)
    min_max=[min(A(:)) max(A(:))];
    f=vpa(min_max);
end


function output_image = load_largest_tif_layer(input_image, org_image_print)
output_image = imread(input_image,1);
if(org_image_print)
    figure ('NumberTitle', 'off', 'Name', 'O.G. image')
    imshow(output_image)
end
end

function output_image =height_crop(input_image, min_height, max_height,height_cropped_DSM_print)
tmp=size(input_image);
output_image=zeros(tmp(1),tmp(2));
   for i =1:tmp(1)
       for j=1:tmp(2)
           if( min_height<input_image(i,j) && input_image(i,j)<max_height)
               output_image(i,j) = input_image(i,j);
           end 
           
       end
   end
   clear tmp;
disp('min and max')
get_min_max(output_image)

if(height_cropped_DSM_print)
    figure ('NumberTitle', 'off', 'Name', 'height_cropped_DSM')
    imshow(output_image)
end 


end

function output_image = tophat_filtering(input_image, tophat_structure_element_size, top_hat_image_print, use_block_proccesing, block_info)
se = strel('disk',tophat_structure_element_size);

if(use_block_proccesing)
    block_size=block_info(1,:);
    border_size=block_info(2,:);

    tophat_fun = @(block_struct) imtophat(block_struct.data,se);% function handle
    output_image = blockproc(input_image,block_size,tophat_fun,'BorderSize',border_size);
else
    output_image=imtophat(input_image,se);
end

if(top_hat_image_print)
    figure ('NumberTitle', 'off', 'Name', 'top_hat')
    imshow(output_image)
end

disp('min and max from tophat_image:')
min_max =get_min_max(output_image)
end



function output_image = opening(input_image, opening_structure_element_size, top_hat_opened_image_print, use_block_proccesing,block_info )
se2 = strel('disk',opening_structure_element_size); 

if(use_block_proccesing)
    block_size=block_info(1,:);
    border_size=block_info(2,:);
    open_fun=@(block_struct) imopen(block_struct.data,se2);% function handle
    output_image = blockproc(input_image,block_size,open_fun,'BorderSize',border_size);
else
    output_image =imopen(input_image,se2); 
end

if(top_hat_opened_image_print)
    figure ('NumberTitle', 'off', 'Name', 'tophat_opened')
    imshow(output_image)
end

disp('min and max from tophat_opened')
get_min_max(output_image)
end

function output_image = regional_maxima(input_image,regional_maxima_image_print,use_block_proccesing,block_info)
if(use_block_proccesing)
    block_size=block_info(1,:);
    border_size=block_info(2,:);
    
    reg_max_fun=@(block_struct) imregionalmax(block_struct.data);% function handle
    output_image = blockproc(input_image,block_size,reg_max_fun,'BorderSize',border_size);
else
    output_image=imregionalmax(input_image);
end

if(regional_maxima_image_print)
    figure ('NumberTitle', 'off', 'Name', 'regional_maxima_opened')
    imshow(output_image)
end 
end

function output_image = polygon_crop(input_image)
figure ('NumberTitle', 'off', 'Name', 'Select the polygon crop to remove outliers')
output_image=roipoly(input_image);
end

function output_image =make_super_image(input_image, org_image, poly_crop_region,min_tree_height, max_tree_height, super_image_print)

tmp=size(org_image);
output_image=zeros(tmp(1),tmp(2));
   for i =1:tmp(1)
       for j=1:tmp(2)
           if(poly_crop_region(i,j) && input_image(i,j) && min_tree_height< input_image(i,j) && max_tree_height>input_image(i,j))
               output_image(i,j) = org_image(i,j);
           end 
           
       end
   end
   clear tmp;
disp('min and max from super_image')
get_min_max(output_image)

if(super_image_print)
    figure ('NumberTitle', 'off', 'Name', 'super_image')
    % surf(super_image,'FaceAlpha',1)
    % colorbar
    imshow(output_image)
end
end

function number_of_trees = count_and_color_plot_approx_of_heights(input_image, super_image_color_print)
[L,number_of_trees] = bwlabel(input_image);
% disp('number of tress:')
number_of_trees

if(super_image_color_print)
    figure ('NumberTitle', 'off', 'Name', 'super_image_color')
    contour(input_image)
    title({'number of trees: ', number_of_trees});
    colorbar
    view(360,270)
end
end

function output = height_indexing(input_image,height_index_span)

CC = bwconncomp(input_image);
S = regionprops(CC,'Centroid');

centriod_matrix=round(vertcat( S.Centroid));


len=length(centriod_matrix);
heighest_tree=max(input_image(:));
number_of_height_catagories=ceil(heighest_tree / height_index_span);

list_of_heights=zeros(1,len);
overview_of_heights=zeros(number_of_height_catagories,1);
for i=1:len
    tmp_value = abs(input_image(centriod_matrix(i, 2),centriod_matrix(i, 1)));   % obs på abs fjerner lidt cm
    centriod_matrix(i,3) = tmp_value;
    ii=1+(floor(tmp_value/height_index_span));
    overview_of_heights(ii)=overview_of_heights(ii)+1;
       
end
height_struct.xyz_coordinates_of_maximas=centriod_matrix;
height_struct.heights_grouped=overview_of_heights;
get_min_max(centriod_matrix(:,3))

disp('number of trees taller than xx')
disp(overview_of_heights(number_of_height_catagories))
output=height_struct;
end