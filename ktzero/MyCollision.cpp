#include "MyCollision.h"

bool MyCollision::CheckCollision(const Box& box1, const Box& box2) {
	// �� �ڽ��� �ּ����� �ִ��� ��ǥ�� �����ɴϴ�.
	Vector3 minPoint1 = box1.mFrontTopLeft;
	Vector3 maxPoint1 = box1.mBackBottomRight;
	Vector3 minPoint2 = box2.mFrontTopLeft;
	Vector3 maxPoint2 = box2.mBackBottomRight;

	// �� �ڽ��� �浹�ϴ��� ���θ� �˻��մϴ�.
	if (minPoint1.getX() <= maxPoint2.getX() && maxPoint1.getX() >= minPoint2.getX() &&
		minPoint1.getY() <= maxPoint2.getY() && maxPoint1.getY() >= minPoint2.getY() &&
		minPoint1.getZ() <= maxPoint2.getZ() && maxPoint1.getZ() >= minPoint2.getZ()) {
		// �� �ڽ��� �浹�ϸ� true�� ��ȯ�մϴ�.

		return true;
	}

	// �� �ڽ��� �浹���� ������ false�� ��ȯ�մϴ�.
	return false;
}