cmd_/home/ubuntu/pi_bsp/drivers/p432_ledkey_poll/Module.symvers :=  sed 's/ko$$/o/'  /home/ubuntu/pi_bsp/drivers/p432_ledkey_poll/modules.order | scripts/mod/modpost -m -a    -o /home/ubuntu/pi_bsp/drivers/p432_ledkey_poll/Module.symvers -e -i Module.symvers -T - 
