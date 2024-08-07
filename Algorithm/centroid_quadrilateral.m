function ans = centroid_quadrilateral(a,b,c,d)
 ans = zeros(4,2);
 ans(1, :) = [(a(1) + b(1) + c(1)) / 3, (a(2) + b(2) + c(2)) / 3];
 ans(2, :) = [(d(1) + b(1) + c(1)) / 3, (d(2) + b(2) + c(2)) / 3];
 ans(3, :) = [(d(1) + a(1) + c(1)) / 3, (d(2) + a(2) + c(2)) / 3];
 ans(4, :) = [(d(1) + b(1) + a(1)) / 3, (d(2) + b(2) + a(2)) / 3];
 


  