a=[5,2,1,3,4,5];
fid = fopen('break.txt', 'wt+'); %'wt' for writing in text mode
fprintf(fid,'%f ',a);
fclose(fid);
quit
