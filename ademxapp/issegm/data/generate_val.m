
% Root directory is w.r.t the data folder within the highest layer of repo
data_root_directory = 'kitti/data_odometry/sequence';

% If there is any subdirectory for sequence index
sequence = '00';

% The stuff in the file name before the index, if any
% Can also be used to specify if there is a subdirecotry for multiple
% cameras, such as this KITTI example
filename_prefix = 'image_0/';
% The stuff in the file name after the index but before the extension, if 
% any
filename_suffix = '';

filetype = 'png';

% How many characters is the index padded to
padding_len = 5;
index_format = ['%0', num2str(padding_len), '.f'];

% MatLab starts counting from 0, but shouldn't matter here
max_index = 1000;

% Only as a place holder for evaluation, not actually used
% Feel free to change to any grey scale images
dummy_gt_label = 'gtFine/val/frankfurt/frankfurt_000000_000294_gtFine_labelIds.png';

lst_file = fopen('val.lst', 'w');

for i = 0:max_index
    index_str = num2str(i, index_format);
    image_path = [data_root_directory, '/', sequence, '/', filename_prefix, index_str, filename_suffix, '.', filetype];
    this_line = sprintf([image_path, '\t', dummy_gt_label, '\n']);
    fprintf(lst_file, this_line);
end

fclose(lst_file);

