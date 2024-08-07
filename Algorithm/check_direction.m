function ans = check_direction(A,B,C,D,distance_A,distance_B,distance_C,distance_D)   
%checking if the quadrlateral is formed in the inner sides of the circle or
%outer sides of the circle. gives a flag 
    delta3 = 0;
    delta2 = 0;
    ans = drawa_quad(A,B,C,D,distance_A,distance_B,distance_C,distance_D);
    X = [ans(1,1),ans(1,2)];
    delta2 = ans(2,1);
    delta3 = delta3 + ans(2,1);
    distance_A = distance_A + delta2;
    distance_B = distance_B + delta2;
    distance_C = distance_C + delta2;
    distance_D = distance_D + delta2;
    ans = drawa_quad(A,B,C,D,distance_A,distance_B,distance_C,distance_D);
    X = [ans(1,1),ans(1,2)];
    delta2 = ans(2,1);
    if delta2 > delta3
        ans = 0;
    else
        ans = 1;
    end
end