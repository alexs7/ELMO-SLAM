
filename = 'poses.txt';
file = fopen(filename, 'r');


format = '%d %f %f %f %f %f %f %f %f %f %f %f %f';
sizeContent = [13, Inf];
content = fscanf(file, format, sizeContent);
fclose(file);

content = content';


indices = content(:, 1);
full_len = indices(end);
full_content = NaN*ones(full_len, 12);

len = length(indices);
for i = 1:(len-1)
    for j = indices(i):(indices(i+1)-1)
        full_content(j, :) = content(i, 2:13);
    end
end
full_content(end, :) = content(end, 2:13);

filename_out = 'poses_kitti.txt';
file_out = fopen(filename_out, 'w');

format_out = '%f %f %f %f %f %f %f %f %f %f %f %f\n';
fprintf(file_out, format_out, full_content');
fclose(file_out);
