cmd_/home/ubuntu/pi_bsp/drivers/p527_ledkey_proc/p527_ledkey_dev.mod := printf '%s\n'   p527_ledkey_dev.o | awk '!x[$$0]++ { print("/home/ubuntu/pi_bsp/drivers/p527_ledkey_proc/"$$0) }' > /home/ubuntu/pi_bsp/drivers/p527_ledkey_proc/p527_ledkey_dev.mod