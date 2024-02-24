#include <iostream>

int main()
{
	float h = 0;
	float m = 59;

	std::cout << "Hour: ";
	std::cin >> h;
	std::cout << "Minute: ";
	std::cin >> m;

	constexpr float degreesPerHour = 30; // 360 / 12
	constexpr float degreesPerMinute = 6; // 360 / 60

	float HourAngle = h * degreesPerHour + (m / 60) * degreesPerHour;
	float MinuteAngle = m * degreesPerMinute;

	float Angle = abs(HourAngle - MinuteAngle);

	if (Angle > 180) // 360 / 2
		Angle = 360 - Angle;

	std::cout << "Angle: ";
	printf("%.1f", abs(Angle));
}