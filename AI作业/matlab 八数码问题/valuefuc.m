function fuc = valuefuc(state, dis)
% �����������Ӻ�������ֵ����
% �������Ϊ��ǰ״̬��Ŀ��״̬
% ͨ�����뷨�����ֵ����

s1 = 0;

[x, y] = find(state.point_of_start == 1);% �������1�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 1);% �������1��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 2);% �������2�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 2);% �������2��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 3);% �������3�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 3);% �������3��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 4);% �������4�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 4);% �������4��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 5);% �������5�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 5);% �������5��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 6);% �������6�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 6);% �������6��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 7);% �������7�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 7);% �������7��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

[x, y] = find(state.point_of_start == 8);% �������8�ڵ�ǰ״̬��λ��
[x1, y1] = find(dis == 8);% �������8��Ŀ��״̬��λ��
s1 = s1 + abs(x - x1) + abs(y - y1);

fuc = s1;
end