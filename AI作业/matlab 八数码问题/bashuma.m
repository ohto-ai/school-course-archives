function [ ]=bashuma
% ������������������������matlab�����иú������� 
% �ú������������ʼ�������Ѱ��·�����������е㣬������Գɹ��������·�����
% �ں����У�Ԥ����state.point_of_startΪ��㣬�� point_of_aimΪ�е�


%% �������ڼ�����ȫ�ֱ���
global count_in_openlist;  %open�����
global count_in_closelist;  %close�����
global time_of_loop;  %ѭ����������

count_in_openlist=1; % ��ʼ�������ֵΪ1
count_in_closelist=0; % ��ʼ��close����ֵΪ0
time_of_loop=0; % ��ʼ��ѭ����������Ϊm

% ��ʼ����ʼֵ��Ŀ��ֵ


point_of_aim = [ 
    1 2 3;
    8 0 4;
    7 6 5
        ]; % Ŀ��ڵ�
state.point_of_start = [
    7 5 3;
    1 6 4;
    2 8 0
        ]; % ��ʼ�ڵ�
state.prev = zeros(3); % �м�״̬�ڵ�
state.num = 1; % �任������¼
state.fuc = valuefuc( state, point_of_aim ); % ѡ��
open(1) = state ; %��ʼ��Open��
current_state = state;

%% �����ѭ��
find_the_aim_point = 0;
while find_the_aim_point == 0
    time_of_loop = time_of_loop + 1;
    
    % ������㹻��Ĵ�����û���ҵ���Ч�Ľ⣬�ж�����
    if time_of_loop >= 10000
        disp('error!!');
        break;
    end
    
    % ��OPEN����Ѱ�Ҵ�����Сֵ
    for j = 1 : count_in_openlist
        if current_state.fuc > open(j).fuc
            current_state = open(j);
        end
    end
    
    % ���ҵ�����С��������CLOSE��
    count_in_closelist = count_in_closelist+1;
    index_of_state = current_state.num;
    close(count_in_closelist) = current_state;
    close(count_in_closelist).num = count_in_closelist;
    
    % ��OPEN����С�Ĵ���ֵɾ��
    open(index_of_state).point_of_start = zeros(3);
    open(index_of_state).fuc = inf;
    
    % �ж�close�����Ƿ���Ŀ��ڵ㣬����У���������
    find_the_aim_point = 0;
    find_the_aim_point = getit(close,point_of_aim);
    if find_the_aim_point == 1
        disp('success!!');
        break;
    end
    
    % ���û�н�����չ�ڵ����
    open = opera(open, close, current_state, point_of_aim);
    current_state.fuc = inf;
end

%����ܹ��ҵ����ŵĽ⣬�����Ž��·�����������
trace_to_start = 0;
state_used_in_trace = point_of_aim;
n = 0;

while 1  % ��ѭ����ֱ�����ݵ���ʼ����ֹ
    for j = 1 : count_in_closelist % ����close���
        if state_used_in_trace == zeros(3) % ������ݵ�0�������
            trace_to_start = 1; % ���������Ϊ0
            break;
        end

        if close(j).point_of_start == state_used_in_trace % ���ݵ�ǰһ���ڵ���������л���
            state_close_to_show = close(j).num;
            n = n+1;
            show(n) = state_close_to_show;
            state_used_in_trace = close(j).prev;
        end
    end
    
    % ������ѭ��
    if trace_to_start==1
        break;
    end

end
% ���д�ӡ
for j=1:n
    close(show(n+1-j)).point_of_start
end

end

%��ѯ�Ƿ��ҵ�Ŀ��ڵ�
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