clear all; clc;

tic

MIN_VERTICES = 2;
MAX_VERTICES = 8;
N_POLYGONS = 12;
OFFSET_MULT = 3;
RASTER_SIZE = [800, 800];


polygons = struct('n_vertices', 0, 'x', [], 'y', [], ...
                 'r', [], 'angles', [], 'color', [0 0 0], 'alpha', 1,...
                 'offset_r', 0, 'offset_angle', 0);
             
polygons(N_POLYGONS).n_vertices = 0;
n_vertices = randi([MIN_VERTICES, MAX_VERTICES], N_POLYGONS); % 1 x n_polygons
for i = 1:N_POLYGONS
    polygons(i).n_vertices = n_vertices(i);
end
    

%generate random polygons and draw
for i = 1:N_POLYGONS
    %polar cord
    r = rand(1, n_vertices(i));
    angles = sort(rand(1, n_vertices(i)) * 2 * pi);
    %offset
    offset_x = rand(1,1)*OFFSET_MULT;
    offset_y = rand(1,1)*OFFSET_MULT;
    offset_r = sqrt(offset_x^2 + offset_y^2);
    offset_angle = atan(offset_y/offset_x);
    %cartesian cord
    x = r .* cos(angles) + offset_x + 1;
    y = r .* sin(angles) + offset_y + 1;
    rgb_color = rand(1,3);
    alpha = rand(1,1);
    
    %store the polygon
    polygons(i).r = r;
    polygons(i).angles = angles;
    polygons(i).offset_r = offset_r;
    polygons(i).offset_angle = offset_angle;
    polygons(i).x = x;
    polygons(i).y = y;
    polygons(i).color = rgb_color;
    polygons(i).alpha = alpha;

end


%plot vector
figure(1)
% subplot(1,2,1);
hold on;
for i = 1:N_POLYGONS
    p = patch(polygons(i).x, polygons(i).y, polygons(i).color, 'FaceAlpha', ...
              polygons(i).alpha);
end


%create raster
R = zeros(RASTER_SIZE(1), RASTER_SIZE(2), 3); %RGB
for i = 1:N_POLYGONS
    mask = poly2mask(polygons(i).x * RASTER_SIZE(1) / (2 + OFFSET_MULT), ...
                     RASTER_SIZE(2) - polygons(i).y * RASTER_SIZE(2) / (2 + OFFSET_MULT) , ...
                     RASTER_SIZE(1), RASTER_SIZE(2));
    R(:,:, 1) = R(:,:, 1) + mask * polygons(i).color(1) * polygons(i).alpha;
    R(:,:, 2) = R(:,:, 2) + mask * polygons(i).color(2) * polygons(i).alpha;
    R(:,:, 3) = R(:,:, 3) + mask * polygons(i).color(3) * polygons(i).alpha;
   
end
figure(2)
% subplot(1,2,2); hold on;
imshow(R)    

toc



    


