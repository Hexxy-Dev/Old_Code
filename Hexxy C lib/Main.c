#include "Hexxy/Macros.h"
#include "Hexxy/Math/vec3.h"
#include "Hexxy/Math/Random.h"

int main()
{
	check_compiler_version();

	random_init();

	vec3 v1 = vec3_create(1.0f);
	vec3 v2 = vec3_create(2.0f, 3.0f, 1.0f);

	vec3 v3 = vec3_multiply(v1, v2);
	vec3_print(&v3);

	float t = 2.0f;
	v3 = vec3_multiply(v3, t);

	vec3_print(&v3);
}