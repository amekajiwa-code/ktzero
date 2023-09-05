#include "OBB.h"
#include <cmath>

Vector2 OBB::GetHeightVec(Rect rt)
{
    Vector2 heightVec;

    // ���� ���� ���
    heightVec.mX = rt.m_fWidth * cos(DegreeToRadian(rt.mAngle - 90)) * 0.5f;
    heightVec.mY = rt.m_fWidth * sin(DegreeToRadian(rt.mAngle - 90)) * 0.5f;

    return heightVec;
}

Vector2 OBB::GetWidthVec(Rect rt)
{
    Vector2 widthVec;

    // �ʺ� ���� ���
    widthVec.mX = rt.m_fHeight * cos(DegreeToRadian(rt.mAngle)) * 0.5f;
    widthVec.mY = rt.m_fHeight * sin(DegreeToRadian(rt.mAngle)) * 0.5f;

    return widthVec;
}

bool OBB::RectToRect(Rect& rect1, Rect& rect2)
{
    // �� OBB�� �߽� �� �Ÿ� ���� ���
    Vector2 distanceVec = rect2.m_Center - rect1.m_Center;

    // �� OBB�� ���� ���� ���
    Vector2 vec[4] = { GetHeightVec(rect1), GetHeightVec(rect2), GetWidthVec(rect1), GetWidthVec(rect2) };
    float sum = 0.0f;

    for (int i = 0; i < 4; ++i)
    {
        // ���� ����ȭ
        vec[i].Normalize();
        float dotProduct = fabs(vec[i] | distanceVec); // ���밪�� ���� ���� ���
        sum += dotProduct;

        // �� ���� ���Ϳ� �Ÿ� ���� ������ ������ �̿��Ͽ� �浹 �˻�
        if (dotProduct > (rect1.m_fWidth * 0.5f + rect2.m_fWidth * 0.5f))
            return false;
    }

    // ��� ���� ���Ϳ� ���� ������ �պ��� ũ�ٸ� �浹
    if (fabs(distanceVec | vec[0]) > sum || fabs(distanceVec | vec[1]) > sum)
        return false;

    return true;
}
