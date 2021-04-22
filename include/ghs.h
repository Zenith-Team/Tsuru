#pragma once

extern "C" {

	void __deleted_virtual_called();
	void __memzero(void *, int);

	int __ghs_strlen(const char *);
	void __gh_memclr32(void *, int);

	float sinf(float);
	float cosf(float);
	float atan2f(float, float);
}
