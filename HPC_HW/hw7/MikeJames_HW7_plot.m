yyaxis left;
x = [1, 2, 3, 4];
y = [44.458 20.6775 14.1736 10.7502];
s1 = 44.458 / 44.458;
s2 = 44.458 / 20.6775;
s3 = 44.458 / 14.1736;
s4 = 44.458 / 10.7502;
r = [s1 s2 s3 s4];
plot(x,y);
ylabel('Time (seconds)');
yyaxis right;
plot(x,r);
ylabel('Speedup (fold increase)');
title('Number of Processors vs. time and speedup')