cmd_/home/ubuntu/pi_bsp/drivers/p399_ledkey_blockio/ledkey_dev.mod := printf '%s\n'   ledkey_dev.o | awk '!x[$$0]++ { print("/home/ubuntu/pi_bsp/drivers/p399_ledkey_blockio/"$$0) }' > /home/ubuntu/pi_bsp/drivers/p399_ledkey_blockio/ledkey_dev.mod