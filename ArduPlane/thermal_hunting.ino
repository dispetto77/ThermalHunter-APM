
 static void ThermalHunting()
 {
    static FlightMode previous_control_mode;
    
    static bool still_in_thermal;
    
    static bool soaring_debouncer;
    
    unsigned long m_thermal_timer;
     
    if(control_mode == AUTO)
    {
     if (read_climb_rate() > g.thermal_vspeed  && current_loc.alt >= thermal_hunting_min_altitude  && current_loc.alt < thermal_hunting_max_altitude) {
      if (soaring_debouncer == false) {
          soaring_debouncer = true;
          return;
          }
     prev_WP = next_WP;
     set_mode(LOITER);
     throttle_suppressed = true;
     previous_control_mode = AUTO;
     still_in_thermal = true;
     m_thermal_timer = (5000 + millis());
     soaring_debouncer = false;
     return;
      }
    }
    
    if(control_mode == LOITER && previous_control_mode == AUTO && still_in_thermal == true)
    { 
     if (read_climb_rate() < 0 || current_loc.alt >= thermal_hunting_max_altitude  || current_loc.alt < thermal_hunting_min_altitude) {
         
       if (soaring_debouncer == false) {
            soaring_debouncer = true;
            
        if (g.loiter_radius < 0) {
            th_loiter_radius = th_loiter_radius + 1;
            } else {
            th_loiter_radius = th_loiter_radius - 1;
            }
            
         l_radius_vector = (l_radius_vector) * (-1) ;
         
         m_thermal_timer = (5000 + millis());
         
         return;
       }
       if(millis() > (m_thermal_timer)) {
       throttle_suppressed = false;     
       set_mode(AUTO);
       next_WP = prev_WP;
       prev_WP = current_loc;
       previous_control_mode = LOITER;
       soaring_debouncer = false;
       still_in_thermal = false;
       return;
       }
       else{
        if (g.loiter_radius < 0) {
            th_loiter_radius = th_loiter_radius + 1;
            } else {
            th_loiter_radius = th_loiter_radius - 1;
            }
        return;    
         }   
      }
        else { 
            if (abs(th_loiter_radius) <= abs(g.loiter_radius)) l_radius_vector = (l_radius_vector) * (-1);
            if (abs(th_loiter_radius) > (abs(g.loiter_radius) + 60) ) l_radius_vector = (l_radius_vector) * (-1);
            if (g.loiter_radius < 0) th_loiter_radius = th_loiter_radius - l_radius_vector;
            else th_loiter_radius = th_loiter_radius + l_radius_vector;
             }
        return;
    }
   

  }
  
  
