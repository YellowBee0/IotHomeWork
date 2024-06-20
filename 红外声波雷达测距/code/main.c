int main(void)
{
  /* USER CODE BEGIN 1 */
 
  /* USER CODE END 1 */
 
  /* MCU Configuration--------------------------------------------------------*/
 
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
 
  /* USER CODE BEGIN Init */
 
  /* USER CODE END Init */
 
  /* Configure the system clock */
  SystemClock_Config();
 
  /* USER CODE BEGIN SysInit */
 
  /* USER CODE END SysInit */
 
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  OLED_CLS();
  Hcsr04Init(&htim2, TIM_CHANNEL_1);  // 通道选择
  Hcsr04Start();  //  启动超声波
  /* USER CODE END 2 */
 
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
 
    /* USER CODE BEGIN 3 */
  
  //显示实验对比
  OLED_ShowCN_STR(30,0,0,4);
  
  //红外测距显示
  HAL_ADC_Start(&hadc1);
        adcx=HAL_ADC_GetValue(&hadc1);
  distance=DistanceSensor_Get_Val();
  OLED_ShowCN_STR(0,2,4,5);
  OLED_Showdecimal(80,2,distance,3,2,16);
  
  
  //超声波测距显示
  Hcsr04Start();
  OLED_ShowCN_STR(0,4,9,5);
  OLED_Showdecimal(80,4,Hcsr04Read(),3,2,16);
 
  //显示单位
  OLED_ShowCN_STR(30,6,14,5);
    
  }
  /* USER CODE END 3 */
}