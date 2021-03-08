/*
  system.c - Handles system level commands and real-time processes
  Part of Grbl

  Copyright (c) 2014-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

float ManualHomePos[4];
float L1,L2,L1_2,L2_2;

uint8_t angle_mode=false;
bool scara_home = false;	

 

void Init_Scara(){

  ManualHomePos[0] = -settings.scara_theta; //MANUAL_X_HOME_POS
  ManualHomePos[1] = settings.scara_psi; //MANUAL_Y_HOME_POS
  ManualHomePos[2] = MANUAL_Z_HOME_POS;
  ManualHomePos[3] = MANUAL_A_HOME_POS;
  L1 =settings.scara_arm1; 
  L2 =settings.scara_arm2; 
  L1_2 = sq(settings.scara_arm1);
  L2_2 = sq(settings.scara_arm2);  
}

void forward_kinematics_SCARA(float const *f_scara, float *cartesian)
{
    float x_sin, x_cos, y_sin, y_cos;

    x_sin = sin(RADIANS(f_scara[X_AXIS])) * L1;
    x_cos = cos(RADIANS(f_scara[X_AXIS])) * L1;
    y_sin = sin(RADIANS(f_scara[Y_AXIS])) * L2;//��Y�������С���������������ϵ��ת�Ƕ�ʱʹ�ô˹�ʽ
    y_cos = cos(RADIANS(f_scara[Y_AXIS])) * L2;//��Y�������С���������������ϵ��ת�Ƕ�ʱʹ�ô˹�ʽ

    cartesian[X_AXIS] = -x_cos - y_cos - SCARA_OFFSET_X;  //����û�����ϵ��Xֵ
    cartesian[Y_AXIS] = x_sin + y_sin - SCARA_OFFSET_Y;  //����û�����ϵ��Yֵ
    cartesian[Z_AXIS] = (float)f_scara[Z_AXIS];
	cartesian[A_AXIS] = (float)f_scara[A_AXIS];

}

void inverse_kinematics(float const *cartesian, float *f_scara)
{
    float SCARA_pos[2];

    static float SCARA_C2, SCARA_S2, SCARA_K1, SCARA_K2, SCARA_theta, SCARA_psi;

    SCARA_pos[X_AXIS] = -cartesian[X_AXIS] - SCARA_OFFSET_X;  //����������ϵ��Xֵ��ȡ��
    SCARA_pos[Y_AXIS] = cartesian[Y_AXIS] + SCARA_OFFSET_Y;  //����������ϵ��Yֵ

    SCARA_C2 =   ( sq(SCARA_pos[X_AXIS]) + sq(SCARA_pos[Y_AXIS]) - L1_2 - L2_2 ) /(2*L1*L2);
    SCARA_S2 = sqrtf( 1 - sq(SCARA_C2) );

    SCARA_K1 = L1_2 + L2_2 * SCARA_C2;
    SCARA_K2 = L2_2 * SCARA_S2;

    SCARA_theta = ( atan2f(SCARA_K1, SCARA_K2)-atan2f(SCARA_pos[X_AXIS],SCARA_pos[Y_AXIS]) ) ;//�����ת�Ƕȣ���������-X��н�
    SCARA_psi   =   atan2f(SCARA_S2,SCARA_C2) + SCARA_theta;//С����ת�Ƕȣ���Y�������С���������������ϵ��ת�Ƕ�ʱʹ�ô˹�ʽ
		
		if(!angle_mode)
		{
				f_scara[X_AXIS] = DEGREES(SCARA_theta); //�����ת�Ƕ�ת��Ϊ����
				f_scara[Y_AXIS] = DEGREES(SCARA_psi);   //С����ת�Ƕ�ת��Ϊ����
				f_scara[Z_AXIS] = cartesian[Z_AXIS];
				f_scara[A_AXIS] = cartesian[A_AXIS];
		}
		else
		{
				f_scara[X_AXIS] = cartesian[X_AXIS]; 
				f_scara[Y_AXIS] = cartesian[Y_AXIS]; 
				f_scara[Z_AXIS] = cartesian[Z_AXIS];	
				f_scara[A_AXIS] = cartesian[A_AXIS];				
		
		}
}

void scara_report_positions() 
{
		uint8_t idx;
		static float position_scara[3];
		
    for (idx=0; idx<N_AXIS; idx++)
    {
        position_scara[idx] = system_convert_axis_steps_to_mpos(sys.position, idx);
    }
		printPgmString(PSTR("SCARA Theta:"));
    printFloat(position_scara[X_AXIS],2);
		printPgmString(PSTR("   Psi+Theta:"));
    printFloat(position_scara[Y_AXIS],2);
		printPgmString(PSTR("\n"));		

}

void scara_report_home_pos(uint8_t idx) 
{	
		static float position_scara;
		position_scara = system_convert_axis_steps_to_mpos(sys.position, idx);		
		switch(idx){
		case 0: 
				if (scara_home) {
					ManualHomePos[0] = position_scara;
					settings.scara_theta = - position_scara;
					}
				printPgmString(PSTR("SCARA Psi:"));
                scara_home = false;				
				break;
		case 1: 
				position_scara = position_scara + 135;
				if (scara_home) {
					    ManualHomePos[1] = position_scara;
						settings.scara_psi = position_scara;
				    }
				printPgmString(PSTR("SCARA Theta:")); 
				break;
		}
		printFloat(position_scara,2);
        printPgmString(PSTR("\n"));			

}

