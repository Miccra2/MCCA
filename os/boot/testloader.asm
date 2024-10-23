.section .boot
.global _boot

_boot:    

.space 510 - (. - _boot), 0
.word 0xAA55

.size _boot, . - _boot
