function [] = search(state, op, cl)
% 八数码问题子函数，用于寻找state 是否在open表中和close表中。
% 输入变量为当前状态， open 表，close 表
% 在函数中改变全局变量的索引值，供函数外引用。

global count_in_openlist;
global count_in_closelist;

for j = 1 : count_in_openlist-1
    if  op(j).point_of_start == state.point_of_start
        count_in_openlist = count_in_openlist-1;
        break
    end
end

for j = 1 : count_in_closelist - 1
    if cl(j).point_of_start == state.point_of_start
        count_in_openlist = count_in_openlist - 1;
        break;
    end
end
end