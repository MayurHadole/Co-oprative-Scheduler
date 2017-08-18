




//------------------------------------------------------------------------------
// Function Name : s_init
// Description : Send Instruction Function (RS=0 & RW=0)
//------------------------------------------------------------------------------

void s_init() 
{
functionCmd(10,0); //Initialize RS=0 for selecting instruction Send
functionCmd(9,0); // Select RW=0 to write Instruction/data on LCD


}
//------------------------------------------------------------------------------
// Function Name : s_data
// Description : Send Data Select routine(RS=1 & RW=0)
//------------------------------------------------------------------------------

void s_data() 
{
functionCmd(10,1); //Initialize RS=0 for selecting instruction Send
functionCmd(9,0); // Select RW=0 to write Instruction/data on LCD

}
//------------------------------------------------------------------------------
// Function Name : s_latch
// Description : Latch Data/Instruction on LCD Databus.
//------------------------------------------------------------------------------

void s_latch() 
{
enable(1);
Delay(10);
enable(0);
Delay(10);
}



//Writes H. DDRAM has already been selected by initialization when the power was turned on.
//The cursor is incremented by one and shifted to the right.
/*Delay(400);
functionCmd(10,1);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,1);
functionCmd(5,0);
functionCmd(4,0);
functionCmd(3,1);//
functionCmd(2,0);//
functionCmd(1,0);
functionCmd(0,0);
Delay(70);
enable(0);*/
//functionCmd(10,0);


void testpin(int mode)
{
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_10);
Delay(10);
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_10);
}

ADD_CMD("test",testpin,"	prints commands on lcd");
