function open = opera(op, cl, state, dis)
% 八数码问题子函数，用于执行扩展表的操作
% 输入变量为 open 表，close 表，当前状态， 目标
% 输出为经过拓展的open表

% 主函数中声明的全局变量
global count_in_closelist;

[x, y] = find(state.point_of_start == 0);% 找到当前状态中的空位，保存为横纵坐标

if x  ==  1  &&  y  ==  1 % 判断横纵坐标的位置，从而决定移动的方向
    open = rt(state, op, cl, dis); % 空位向右边移动
    open = dn(state, open, cl, dis); % 空位向下边移动
elseif x  ==  1  &&  y  ==  2
    open = lt(state, op, cl, dis); % 空位向左边移动
    open = rt(state, open, cl, dis);% 空位向右边移动
    open = dn(state, open, cl, dis);% 空位向下边移动
elseif x == 1 && y == 3
    open = lt(state, op, cl, dis);% 空位向左边移动
    open = dn(state, open, cl, dis);% 空位向下边移动
elseif x == 2 && y == 1
    open = up(state, op, cl, dis); % 空位向上边移动
    open = rt(state, open, cl, dis);% 空位向右边移动
    open = dn(state, open, cl, dis);% 空位向下边移动
elseif x == 2 && y == 2
    open = lt(state, op, cl, dis);% 空位向左边移动
    open = up(state, open, cl, dis);% 空位向上边移动
    open = rt(state, open, cl, dis);% 空位向右边移动
    open = dn(state, open, cl, dis);% 空位向下边移动
elseif x == 2 && y == 3
    open = lt(state, op, cl, dis);% 空位向左边移动
    open = up(state, open, cl, dis);% 空位向上边移动
    open = dn(state, open, cl, dis);% 空位向下边移动
elseif x == 3 && y == 1
    open = up(state, op, cl, dis);% 空位向上边移动
    open = rt(state, open, cl, dis);% 空位向右边移动
elseif x == 3 && y == 2
    open = lt(state, op, cl, dis);% 空位向左边移动
    open = up(state, open, cl, dis);% 空位向上边移动
    open = rt(state, open, cl, dis);% 空位向右边移动
elseif x == 3 && y == 3
    open = lt(state, op, cl, dis);% 空位向左边移动
    open = up(state, open, cl, dis);% 空位向上边移动
end
end

function open = rt(state, op, cl, dis)
% 八数码问题子函数，用于执行向右移动空位的操作
% 输入变量为当前状态， open 表，close 表， 目标
% 输出为经过拓展的open表

% 全局变量
global count_in_openlist;

count_in_openlist = count_in_openlist+1; % 将open表的计数增加1
s = state;

[x, y] = find(s.point_of_start  ==  0);% 找到当前状态中的空位，保存为横纵坐标

% 进行交换数字
t = s.point_of_start(x, y+1);
s.point_of_start(x, y+1) = 0;
s.point_of_start(x, y) = t;

s.num = count_in_openlist; % 计算层数

% 更新open表的数据
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end

function open = up(state, op, cl, dis)
% 八数码问题子函数，用于执行向下移动空位的操作
% 输入变量为当前状态， open 表，close 表， 目标
% 输出为经过拓展的open表
% 操作步骤与rt(state, op, cl, dis)类似，注释不一一列写

global count_in_openlist;

count_in_openlist = count_in_openlist+1;% 将open表的计数增加1
s = state;

[x, y] = find(s.point_of_start  ==  0);
t = s.point_of_start(x-1, y);
s.point_of_start(x-1, y) = 0;
s.point_of_start(x, y) = t;
s.num = count_in_openlist;% 计算层数

% 更新open表的数据
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end

function open = lt(state, op, cl, dis)
global count_in_openlist;

count_in_openlist = count_in_openlist + 1;% 将open表的计数增加1
s = state;

[x, y] = find(s.point_of_start  ==  0);
t = s.point_of_start(x, y-1);
s.point_of_start(x, y-1) = 0;
s.point_of_start(x, y) = t;
s.num = count_in_openlist;% 计算层数

% 更新open表的数据
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end

function open = dn(state, op, cl, dis)
% 八数码问题子函数，用于执行向上移动空位的操作
% 输入变量为当前状态， open 表，close 表， 目标
% 输出为经过拓展的open表
% 操作步骤与rt(state, op, cl, dis)类似，注释不一一列写

global count_in_openlist;

count_in_openlist = count_in_openlist+1;% 将open表的计数增加1
s = state;

[x, y] = find(s.point_of_start  ==  0);
t = s.point_of_start(x+1, y);
s.point_of_start(x+1, y) = 0;
s.point_of_start(x, y) = t;
s.num = count_in_openlist;% 计算层数

% 更新open表的数据
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end
