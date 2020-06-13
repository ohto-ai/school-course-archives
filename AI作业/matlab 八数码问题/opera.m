function open = opera(op, cl, state, dis)
% �����������Ӻ���������ִ����չ��Ĳ���
% �������Ϊ open ��close ����ǰ״̬�� Ŀ��
% ���Ϊ������չ��open��

% ��������������ȫ�ֱ���
global count_in_closelist;

[x, y] = find(state.point_of_start == 0);% �ҵ���ǰ״̬�еĿ�λ������Ϊ��������

if x  ==  1  &&  y  ==  1 % �жϺ��������λ�ã��Ӷ������ƶ��ķ���
    open = rt(state, op, cl, dis); % ��λ���ұ��ƶ�
    open = dn(state, open, cl, dis); % ��λ���±��ƶ�
elseif x  ==  1  &&  y  ==  2
    open = lt(state, op, cl, dis); % ��λ������ƶ�
    open = rt(state, open, cl, dis);% ��λ���ұ��ƶ�
    open = dn(state, open, cl, dis);% ��λ���±��ƶ�
elseif x == 1 && y == 3
    open = lt(state, op, cl, dis);% ��λ������ƶ�
    open = dn(state, open, cl, dis);% ��λ���±��ƶ�
elseif x == 2 && y == 1
    open = up(state, op, cl, dis); % ��λ���ϱ��ƶ�
    open = rt(state, open, cl, dis);% ��λ���ұ��ƶ�
    open = dn(state, open, cl, dis);% ��λ���±��ƶ�
elseif x == 2 && y == 2
    open = lt(state, op, cl, dis);% ��λ������ƶ�
    open = up(state, open, cl, dis);% ��λ���ϱ��ƶ�
    open = rt(state, open, cl, dis);% ��λ���ұ��ƶ�
    open = dn(state, open, cl, dis);% ��λ���±��ƶ�
elseif x == 2 && y == 3
    open = lt(state, op, cl, dis);% ��λ������ƶ�
    open = up(state, open, cl, dis);% ��λ���ϱ��ƶ�
    open = dn(state, open, cl, dis);% ��λ���±��ƶ�
elseif x == 3 && y == 1
    open = up(state, op, cl, dis);% ��λ���ϱ��ƶ�
    open = rt(state, open, cl, dis);% ��λ���ұ��ƶ�
elseif x == 3 && y == 2
    open = lt(state, op, cl, dis);% ��λ������ƶ�
    open = up(state, open, cl, dis);% ��λ���ϱ��ƶ�
    open = rt(state, open, cl, dis);% ��λ���ұ��ƶ�
elseif x == 3 && y == 3
    open = lt(state, op, cl, dis);% ��λ������ƶ�
    open = up(state, open, cl, dis);% ��λ���ϱ��ƶ�
end
end

function open = rt(state, op, cl, dis)
% �����������Ӻ���������ִ�������ƶ���λ�Ĳ���
% �������Ϊ��ǰ״̬�� open ��close �� Ŀ��
% ���Ϊ������չ��open��

% ȫ�ֱ���
global count_in_openlist;

count_in_openlist = count_in_openlist+1; % ��open��ļ�������1
s = state;

[x, y] = find(s.point_of_start  ==  0);% �ҵ���ǰ״̬�еĿ�λ������Ϊ��������

% ���н�������
t = s.point_of_start(x, y+1);
s.point_of_start(x, y+1) = 0;
s.point_of_start(x, y) = t;

s.num = count_in_openlist; % �������

% ����open�������
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end

function open = up(state, op, cl, dis)
% �����������Ӻ���������ִ�������ƶ���λ�Ĳ���
% �������Ϊ��ǰ״̬�� open ��close �� Ŀ��
% ���Ϊ������չ��open��
% ����������rt(state, op, cl, dis)���ƣ�ע�Ͳ�һһ��д

global count_in_openlist;

count_in_openlist = count_in_openlist+1;% ��open��ļ�������1
s = state;

[x, y] = find(s.point_of_start  ==  0);
t = s.point_of_start(x-1, y);
s.point_of_start(x-1, y) = 0;
s.point_of_start(x, y) = t;
s.num = count_in_openlist;% �������

% ����open�������
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end

function open = lt(state, op, cl, dis)
global count_in_openlist;

count_in_openlist = count_in_openlist + 1;% ��open��ļ�������1
s = state;

[x, y] = find(s.point_of_start  ==  0);
t = s.point_of_start(x, y-1);
s.point_of_start(x, y-1) = 0;
s.point_of_start(x, y) = t;
s.num = count_in_openlist;% �������

% ����open�������
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end

function open = dn(state, op, cl, dis)
% �����������Ӻ���������ִ�������ƶ���λ�Ĳ���
% �������Ϊ��ǰ״̬�� open ��close �� Ŀ��
% ���Ϊ������չ��open��
% ����������rt(state, op, cl, dis)���ƣ�ע�Ͳ�һһ��д

global count_in_openlist;

count_in_openlist = count_in_openlist+1;% ��open��ļ�������1
s = state;

[x, y] = find(s.point_of_start  ==  0);
t = s.point_of_start(x+1, y);
s.point_of_start(x+1, y) = 0;
s.point_of_start(x, y) = t;
s.num = count_in_openlist;% �������

% ����open�������
op(count_in_openlist).point_of_start = s.point_of_start;
op(count_in_openlist).prev = state.point_of_start;
op(count_in_openlist).num = count_in_openlist;
op(count_in_openlist).fuc = valuefuc(s, dis);

search(s, op, cl);
open = op;
end
