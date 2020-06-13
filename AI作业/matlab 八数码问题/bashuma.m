function [ ]=bashuma
% 解决八数码问题的主函数，在matlab中运行该函数即可 
% 该函数从任意的起始点出发，寻找路径到达任意中点，如果可以成功，则进行路径输出
% 在函数中，预设以state.point_of_start为起点，以 point_of_aim为中点


%% 设置用于计数的全局变量
global count_in_openlist;  %open表计数
global count_in_closelist;  %close表计数
global time_of_loop;  %循环次数计数

count_in_openlist=1; % 初始化表计数值为1
count_in_closelist=0; % 初始化close计数值为0
time_of_loop=0; % 初始化循环次数计数为m

% 初始化初始值与目标值


point_of_aim = [ 
    1 2 3;
    8 0 4;
    7 6 5
        ]; % 目标节点
state.point_of_start = [
    7 5 3;
    1 6 4;
    2 8 0
        ]; % 初始节点
state.prev = zeros(3); % 中间状态节点
state.num = 1; % 变换次数记录
state.fuc = valuefuc( state, point_of_aim ); % 选定
open(1) = state ; %初始化Open表
current_state = state;

%% 求解主循环
find_the_aim_point = 0;
while find_the_aim_point == 0
    time_of_loop = time_of_loop + 1;
    
    % 如果在足够多的次数还没有找到有效的解，判定错误
    if time_of_loop >= 10000
        disp('error!!');
        break;
    end
    
    % 在OPEN表中寻找代价最小值
    for j = 1 : count_in_openlist
        if current_state.fuc > open(j).fuc
            current_state = open(j);
        end
    end
    
    % 将找到的最小代价添入CLOSE表
    count_in_closelist = count_in_closelist+1;
    index_of_state = current_state.num;
    close(count_in_closelist) = current_state;
    close(count_in_closelist).num = count_in_closelist;
    
    % 在OPEN表将最小的代价值删除
    open(index_of_state).point_of_start = zeros(3);
    open(index_of_state).fuc = inf;
    
    % 判断close表中是否有目标节点，如果有，则程序结束
    find_the_aim_point = 0;
    find_the_aim_point = getit(close,point_of_aim);
    if find_the_aim_point == 1
        disp('success!!');
        break;
    end
    
    % 如果没有进行扩展节点操作
    open = opera(open, close, current_state, point_of_aim);
    current_state.fuc = inf;
end

%如果能够找到最优的解，将最优解的路径进行输出。
trace_to_start = 0;
state_used_in_trace = point_of_aim;
n = 0;

while 1  % 死循环，直到回溯到初始点终止
    for j = 1 : count_in_closelist % 遍历close表格
        if state_used_in_trace == zeros(3) % 如果回溯到0，则结束
            trace_to_start = 1; % 结束标记置为0
            break;
        end

        if close(j).point_of_start == state_used_in_trace % 回溯到前一个节点则继续进行回溯
            state_close_to_show = close(j).num;
            n = n+1;
            show(n) = state_close_to_show;
            state_used_in_trace = close(j).prev;
        end
    end
    
    % 跳出主循环
    if trace_to_start==1
        break;
    end

end
% 进行打印
for j=1:n
    close(show(n+1-j)).point_of_start
end

end

%查询是否找到目标节点
function find_the_aim_point=getit(close, point_of_aim)
global count_in_closelist;
for j=1:count_in_closelist
    if close(j).point_of_start==point_of_aim
        find_the_aim_point=1;
        break;
    else
        find_the_aim_point=0;
    end
end
end