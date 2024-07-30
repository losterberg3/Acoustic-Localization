% Create figure
close all;
figure;
length = 6;
height = 5;
m = 0.3; % marin from the edges of the table.
x = 10;
y = 10;

% Draw rectangle
rectangle('Position', [x, y, length, height], 'EdgeColor', 'r', 'LineWidth', 2);
A = [x,y];
B = [x+length,y];
D = [x,y+height];
C = [x+length,y+height];
hold on; % Allow plots to be overlaid

%name the corners
text(A(1), A(2), 'A', 'HorizontalAlignment', 'right', 'VerticalAlignment', 'bottom');
text(B(1), B(2), 'B', 'HorizontalAlignment', 'right', 'VerticalAlignment', 'bottom');
text(C(1), C(2), 'C', 'HorizontalAlignment', 'right', 'VerticalAlignment', 'bottom');
text(D(1), D(2), 'D', 'HorizontalAlignment', 'right', 'VerticalAlignment', 'bottom');

%random point on the table
%random_x = x + rand() * length;
random_x = (x+m) + ((x+length-m) - (x+m)) * rand();
%random_x = x_min + rand() * (x_max - x_min);
random_y = (y+m) + ((y+height-m) - (y+m)) * rand();
%random_y = y + rand() * height;
%random_x = margin + rand() * (length - 2*margin);
%random_y = margin + rand() * (height - 2*margin);
E = [random_x,random_y]
%E = [12, 11];
delta = 0.01; %rn we are trying negative delta.

distance_A = (sqrt((E(1) - A(1))^2 + (E(2) - A(2))^2))+delta;
distance_D = (sqrt((D(1) - E(1))^2 + (D(2) - E(2))^2))+delta;
distance_C = (sqrt((C(1) - E(1))^2 + (C(2) - E(2))^2))+delta;
distance_B = (sqrt((E(1) - B(1))^2 + (E(2) - B(2))^2))+delta;



%Plot random point
scatter(E(1), E(2), 50, 'filled', 'MarkerFaceColor', 'm');
% Set axis limits to include both rectangle and point
axis equal;

xlim([-10, 30]); % Set x-axis limits
ylim([-10, 30]);
% Set axis labels
xlabel('X-axis');
ylabel('Y-axis');


s = 0;
delta3 = 0; % total error 
delta2 = 0;% error only in reference to the previous loop
X = zeros(1,2);

% Check if delta2 is greater than delta3 for checking the direction of the
% curved sides of the quadrilateral
while s < 20
    f = check_direction(A,B,C,D,distance_A,distance_B,distance_C,distance_D);
    ans = drawa_quad(A,B,C,D,distance_A,distance_B,distance_C,distance_D);
    X = [ans(1,1),ans(1,2)];
    if f==0 
        delta2 = -ans(2,1);%if the quadrilateral is inside of circle area
    else
        delta2 = ans(2,1);%if the quadrilateral is outside of circle area
        
    end
    delta3 = delta3 + ans(2,1);
    %changing the distances according to the errors
    distance_A = distance_A + delta2;
    distance_B = distance_B + delta2; 
    distance_C = distance_C + delta2;
    distance_D = distance_D + delta2;
    s = s+1;
end
scatter(X(1), X(2), 20, 'filled', 'MarkerFaceColor', 'c');
X
delta3
distance_A = (sqrt((E(1) - A(1))^2 + (E(2) - A(2))^2))+delta;
distance_D = (sqrt((D(1) - E(1))^2 + (D(2) - E(2))^2))+delta;
distance_C = (sqrt((C(1) - E(1))^2 + (C(2) - E(2))^2))+delta;
distance_B = (sqrt((E(1) - B(1))^2 + (E(2) - B(2))^2))+delta;


viscircles(A, distance_A, 'Color', 'g', 'LineWidth', 2);
viscircles(B, distance_B, 'Color', 'c', 'LineWidth', 2);
viscircles(C, distance_C, 'Color', 'm', 'LineWidth', 2);
viscircles(D, distance_D, 'Color', 'y', 'LineWidth', 2);




% Title
%getting distances from each point 
% and using them to draw circles from each point

%ans = optimize_point(A,B,C,D,F,distance_A,distance_B,distance_C,distance_D,delta2);


