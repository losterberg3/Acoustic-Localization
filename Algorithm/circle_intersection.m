function [intersection_points] = circle_intersection(x,y,r1,r2)
%calculates the intersection points of two circles guven their radius and
%centers
    x2 = y(1);
    y1 = x(2);
    y2 = y(2);
    % Calculate distance between circle centers
    d = sqrt((x2 - x1)^2 + (y2 - y1)^2);

    % Check if circles intersect
    if d > r1 + r2 || d < abs(r1 - r2)
        intersection_points = []; % Circles do not intersect
        return;
    end

    % Calculate intersection angles
    alpha = acos((r1^2 + d^2 - r2^2) / (2 * r1 * d));
    beta = atan2(y2 - y1, x2 - x1);

    % Calculate intersection points
    intersection_point1 = [x1 + r1 * cos(beta + alpha), y1 + r1 * sin(beta + alpha)];
    intersection_point2 = [x1 + r1 * cos(beta - alpha), y1 + r1 * sin(beta - alpha)];

    % Return intersection points
    intersection_points = [intersection_point1; intersection_point2];
end
