function result = drawa_quad(A,B,C,D,distance_A,distance_B,distance_C,distance_D)
 hold on;
result = zeros(2,2);
 



%viscircles(A, distance_A, 'Color', 'g', 'LineWidth', 2);
%viscircles(B, distance_B, 'Color', 'c', 'LineWidth', 2);
%viscircles(C, distance_C, 'Color', 'm', 'LineWidth', 2);
%viscircles(D, distance_D, 'Color', 'y', 'LineWidth', 2);

intersection_points1 = circle_intersection(D,C,distance_D,distance_C);
intersection_points2 = circle_intersection(D,A,distance_D,distance_A);
intersection_points3 = circle_intersection(B,C,distance_B,distance_C);
intersection_points4 = circle_intersection(B,A,distance_B,distance_A);

%naming the intersection points for easier access
%for i = 1:size(intersection_points1, 1)
    %text(intersection_points1(i, 1), intersection_points1(i, 2), ['1', num2str(i)], 'HorizontalAlignment', 'left', 'VerticalAlignment', 'top');
%end
%for i = 1:size(intersection_points2, 1)
    %text(intersection_points2(i, 1), intersection_points2(i, 2), ['2', num2str(i)], 'HorizontalAlignment', 'left', 'VerticalAlignment', 'top');
%end
%for i = 1:size(intersection_points3, 1)
 %   text(intersection_points3(i, 1), intersection_points3(i, 2), ['3', num2str(i)], 'HorizontalAlignment', 'left', 'VerticalAlignment', 'top');
%end
%for i = 1:size(intersection_points4, 1)
 %   text(intersection_points4(i, 1), intersection_points4(i, 2), ['4', num2str(i)], 'HorizontalAlignment', 'left', 'VerticalAlignment', 'top');
%end

a1 = [intersection_points1(2,1),intersection_points1(2,2)];
b1 = [intersection_points2(1,1),intersection_points2(1,2)];
c1 = [intersection_points3(1,1),intersection_points3(1,2)];
d1 = [intersection_points4(2,1),intersection_points4(2,2)];
cp = centre_quadrilateral(a1,b1,c1,d1);

%xyz = a1-b1;
x1 = [cp(1,1), cp(2,1)];
y1 = [cp(1,2), cp(2,2)];

% Endpoints of line 2
x2 = [cp(3,1), cp(4,1)];
y2 = [cp(3,2), cp(4,2)];

% Calculate slopes (m)
m1 = (y1(2) - y1(1)) / (x1(2) - x1(1));
m2 = (y2(2) - y2(1)) / (x2(2) - x2(1));

% Calculate y-intercepts (b)
b1 = y1(1) - m1 * x1(1);
b2 = y2(1) - m2 * x2(1);

% Find intersection point
x_intersect = (b2 - b1) / (m1 - m2);
y_intersect = m1 * x_intersect + b1;

F = [x_intersect, y_intersect];%the point we are taking temporarily to measure how
% close we are to our rresult and what the error is


F1= sqrt((F(1) - A(1))^2 + (F(2) - A(2))^2) - distance_A ;% Distance to A circle edge
F2= sqrt((F(1) - B(1))^2 + (F(2) - B(2))^2) - distance_B ;% Distance to B circle edge
F3= sqrt((F(1) - C(1))^2 + (F(2) - C(2))^2) - distance_C; % Distance to C circle edge
F4= sqrt((F(1) - D(1))^2 + (F(2) - D(2))^2) - distance_D ; % Distance to D circle edge
delta2 = abs(F1+F2+F3+F4)/4; %average distance from the point to the circle edges(basically the percentage of error
%threshold = exp(-14);
%if a1-b1 > exp(-14)
  %  s = 1;
%else 
 %   s = 0;
%end
delta2 = 0.7*delta2; % using a controlled delta
result(1,1) = F(1);
result(1,2) = F(2);
result(2,1) = delta2;
result(2,2) = 0;
end