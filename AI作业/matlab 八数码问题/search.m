function [] = search(state, op, cl)
% �����������Ӻ���������Ѱ��state �Ƿ���open���к�close���С�
% �������Ϊ��ǰ״̬�� open ��close ��
% �ں����иı�ȫ�ֱ���������ֵ�������������á�

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