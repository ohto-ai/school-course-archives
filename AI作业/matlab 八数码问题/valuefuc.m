function fuc = valuefuc(state, dis)
% 八数码问题子函数，价值函数
% 输入变量为当前状态，目标状态
% 通过距离法计算价值函数

s1 = 0;

[x, y] = find(state.point_of_start == 1);% 获得数字1在当前状态的位置
[x1, y1] = find(dis == 1);% 获得数字1在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 2);% 获得数字2在当前状态的位置
[x1, y1] = find(dis == 2);% 获得数字2在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 3);% 获得数字3在当前状态的位置
[x1, y1] = find(dis == 3);% 获得数字3在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 4);% 获得数字4在当前状态的位置
[x1, y1] = find(dis == 4);% 获得数字4在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 5);% 获得数字5在当前状态的位置
[x1, y1] = find(dis == 5);% 获得数字5在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 6);% 获得数字6在当前状态的位置
[x1, y1] = find(dis == 6);% 获得数字6在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 7);% 获得数字7在当前状态的位置
[x1, y1] = find(dis == 7);% 获得数字7在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 8);% 获得数字8在当前状态的位置
[x1, y1] = find(dis == 8);% 获得数字8在目标状态的位置
s1 = s1 + abs(x - x1) + abs(y - y1);

fuc = s1;
end