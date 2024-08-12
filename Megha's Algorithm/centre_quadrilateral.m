function ans = centre_quadrilateral(a,b,c,d)
  ans = zeros(4,2);
 ans(1, :) = [(a(1) + b(1))/2, (a(2) + b(2))/2];
 ans(2, :) = [(d(1) + c(1))/2, (d(2) + c(2))/2];
 ans(3, :) = [(d(1) + b(1))/2, (d(2) + b(2))/2];
 ans(4, :) = [(a(1) + c(1))/2, (a(2) + c(2))/2];