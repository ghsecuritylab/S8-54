﻿#pragma once


void Ethernet_Init(void);

// Функция будет обрабатывать входной/выходной буфер timeMS миллисекунд. Это надо для передчи больших массивов информации. WARN говнокод. Надо исправить.
void Ethernet_Update(uint timeMS);
