const unsigned char letters[5][92] = {

  {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, //                            
    0x00, 0x00, 0x00, 0x00, //                            
    0xFF, 0xFF, 0xFF, 0x07, // ###########################
    0xFF, 0xFF, 0xFF, 0x07, // ###########################
    0xFF, 0xFF, 0xFF, 0x07, // ###########################
    0x00, 0x1E, 0x00, 0x00, //          ####              
    0x00, 0x0E, 0x00, 0x00, //          ###               
    0x00, 0x07, 0x00, 0x00, //         ###                
    0x80, 0x07, 0x00, 0x00, //        ####                
    0x80, 0x03, 0x00, 0x00, //        ###                 
    0x80, 0x03, 0x00, 0x00, //        ###                 
    0x80, 0x03, 0x00, 0x00, //        ###                 
    0x80, 0x03, 0x00, 0x00, //        ###                 
    0x80, 0x07, 0x00, 0x00, //        ####                
    0x00, 0x0F, 0x00, 0x00, //         ####               
    0x00, 0xFF, 0xFF, 0x07, //         ###################
    0x00, 0xFE, 0xFF, 0x07, //          ##################
    0x00, 0xF8, 0xFF, 0x07, //            ################
    0x00, 0x00, 0x00, 0x00, //                            
    0x00, 0x00, 0x00, 0x00, //                            
    0x00, 0x00, 0x00, 0x00
  },
  
  {
    0x00, 0x00, 0x00, 0x00, //                          
    0x00, 0xFF, 0x01, 0x00, //         #########        
    0xC0, 0xFF, 0x07, 0x00, //       #############      
    0xF0, 0xFF, 0x1F, 0x00, //     #################    
    0xF8, 0x01, 0x3F, 0x00, //    ######       ######   
    0x3C, 0x00, 0x78, 0x00, //   ####             ####  
    0x1E, 0x00, 0xF0, 0x00, //  ####               #### 
    0x0E, 0x00, 0xE0, 0x00, //  ###                 ### 
    0x0E, 0x00, 0xE0, 0x00, //  ###                 ### 
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x0F, 0x00, 0xE0, 0x01, // ####                 ####
    0x0E, 0x00, 0xE0, 0x00, //  ###                 ### 
    0x1E, 0x00, 0xF0, 0x00, //  ####               #### 
    0x3C, 0x00, 0x78, 0x00, //   ####             ####  
    0xF8, 0x00, 0x3E, 0x00, //    #####         #####   
    0xF0, 0x00, 0x1E, 0x00, //     ####         ####    
    0xC0, 0x00, 0x06, 0x00, //       ##         ##      
    0x00, 0x00, 0x00, 0x00  //                          
  },
  
  {
    0x00, 0xFF, 0x01, 0x00, //         #########        
    0xC0, 0xFF, 0x07, 0x00, //       #############      
    0xF0, 0xFF, 0x1F, 0x00, //     #################    
    0xF8, 0x01, 0x3F, 0x00, //    ######       ######   
    0x7C, 0x00, 0x7C, 0x00, //   #####           #####  
    0x1C, 0x00, 0x70, 0x00, //   ###               ###  
    0x1E, 0x00, 0xF0, 0x00, //  ####               #### 
    0x0E, 0x00, 0xE0, 0x00, //  ###                 ### 
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x07, 0x00, 0xC0, 0x01, // ###                   ###
    0x0E, 0x00, 0xE0, 0x00, //  ###                 ### 
    0x1E, 0x00, 0xF0, 0x00, //  ####               #### 
    0x1C, 0x00, 0x70, 0x00, //   ###               ###  
    0x7C, 0x00, 0x7C, 0x00, //   #####           #####  
    0xF8, 0x01, 0x3F, 0x00, //    ######       ######   
    0xF0, 0xFF, 0x1F, 0x00, //     #################    
    0xC0, 0xFF, 0x07, 0x00, //       #############      
    0x00, 0xFF, 0x01, 0x00  //         #########        

  },
  
  {
    0x00, 0x00, 0x00, 0x00, //                          
    0x00, 0x00, 0x00, 0x00, //                          
    0x00, 0x00, 0x00, 0x00, //                          
    0xFF, 0xFF, 0xFF, 0x01, // #########################
    0xFF, 0xFF, 0xFF, 0x01, // #########################
    0xFF, 0xFF, 0xFF, 0x01, // #########################
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x07, 0x70, 0x00, 0x00, // ###         ###          
    0x0F, 0x38, 0x00, 0x00, // ####       ###           
    0x1E, 0x3C, 0x00, 0x00, //  ####     ####           
    0xFE, 0x1F, 0x00, 0x00, //  ############            
    0xF8, 0x0F, 0x00, 0x00, //    #########             
    0xF0, 0x03, 0x00, 0x00, //     ######               
    0x00, 0x00, 0x00, 0x00, //                          
    0x00, 0x00, 0x00, 0x00  //                          
  },
  
  {
    0x00, 0x00, 0x00, 0x00, //                          
    0x00, 0x00, 0x00, 0x00, //                          
    0x00, 0x00, 0x0E, 0x00, //                  ###     
    0xF0, 0x01, 0x3E, 0x00, //     #####        #####   
    0xF8, 0x07, 0x7E, 0x00, //    ########      ######  
    0xFC, 0x07, 0x78, 0x00, //   #########        ####  
    0x1E, 0x0F, 0xF0, 0x00, //  ####   ####        #### 
    0x0E, 0x0E, 0xE0, 0x00, //  ###     ###         ### 
    0x07, 0x1E, 0xE0, 0x01, // ###      ####        ####
    0x07, 0x1C, 0xC0, 0x01, // ###       ###         ###
    0x07, 0x1C, 0xC0, 0x01, // ###       ###         ###
    0x07, 0x3C, 0xC0, 0x01, // ###       ####        ###
    0x07, 0x38, 0xC0, 0x01, // ###        ###        ###
    0x07, 0x38, 0xC0, 0x01, // ###        ###        ###
    0x0F, 0x38, 0xC0, 0x01, // ####       ###        ###
    0x0E, 0x78, 0xE0, 0x01, //  ###       ####      ####
    0x3E, 0x70, 0xE0, 0x00, //  #####      ###      ### 
    0xFC, 0xF0, 0xF0, 0x00, //   ######    ####    #### 
    0xF8, 0xE0, 0x7F, 0x00, //    #####     ##########  
    0xE0, 0xC0, 0x3F, 0x00, //      ###      ########   
    0x00, 0x80, 0x0F, 0x00, //                #####     
    0x00, 0x00, 0x00, 0x00, //                          
    0x00, 0x00, 0x00, 0x00 //
  }
};
