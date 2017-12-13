#define MAXTIMINGS	85
#define DHTPIN		7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };

char* read_dht11_dat();
void readHumidity();

void readHumidity(){
       while(1){
               read_dht11_dat();
               delay(1000);
       }
}

char* read_dht11_dat()
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
 
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
 
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		f = dht11_dat[2] * 9. / 5. + 32;
		printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
			dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );

		char * humidityRepo;
		humidityRepo = malloc(sizeof(char)*255);

		char humidity1[3];
		sprintf(humidity1,"%d",dht11_dat[0]);
		char humidity2[3];
		sprintf(humidity2,"%d",dht11_dat[1]);
		char temperature1[3];
		sprintf(temperature1,"%d",dht11_dat[2]);
		char temperature2[3];
		sprintf(temperature2,"%d",dht11_dat[3]);

		strcat(humidityRepo, "Humidity = ");
		strcat(humidityRepo, humidity1);
		strcat(humidityRepo, ".");
		strcat(humidityRepo, humidity2);
		strcat(humidityRepo, " % Temperature = ");
		strcat(humidityRepo, temperature1);
		strcat(humidityRepo, ".");
		strcat(humidityRepo, temperature2);
		strcat(humidityRepo, " C ");

		return 	humidityRepo;

	}else  {
		printf( "Data not good, skip\n" );

		return "Data not good, skip";
	}

	
}