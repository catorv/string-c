//
//  main.c
//  string-c
//
//  Created by Cator Vee on 10/22/13.
//  Copyright (c) 2013 Cator Vee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "string.h"

void __(string_t label)
{
  printf("\n__%s_________________________________________________\n", label);
}

int main(int argc, const char * argv[])
{
  const string_t s1 = "Created by Cator VeeVee on 10/22/13 (cator)";
  const string_t s2 = "cator";
  const string_t s3 = "Cator";
  const string_t s4 = "Wei";
  
  string_t str;
  
  printf("s1 = '%s' \n", s1);
  printf("s2 = '%s' \n", s2);
  printf("s3 = '%s' \n", s3);
  printf("s4 = '%s' \n", s4);
  
  
  __("strpos"); {
    printf("strpos(s1, s2): %ld \n", strpos(s1, s2));
    printf("stripos(s1, s2): %ld \n", stripos(s1, s2));
    printf("strrpos(s1, s3): %ld \n", strrpos(s1, s3));
    printf("strripos(s1, s3): %ld \n", strripos(s1, s3));
    
    printf("strpos(s1, s4): %ld \n", strpos(s1, s4));
    printf("stripos(s1, s4): %ld \n", stripos(s1, s4));
    printf("strrpos(s1, s4): %ld \n", strrpos(s1, s4));
    printf("strripos(s1, s4): %ld \n", strripos(s1, s4));
  }
  
  
  __("copy_substr"); {
    str = copy_substr(s1, 11, 5);
    printf("copy_substr(s1, 11, 5): '%s'\n", str);
    free(str);
    
    str = copy_substr(s1, -6, 5);
    printf("copy_substr(s1, -6, 5): '%s'\n", str);
    free(str);
    
    str = copy_substr(s1, -6, -1);
    printf("copy_substr(s1, -6, -1): '%s'\n", str);
    free(str);
    
    str = copy_substr(s1, 34, 10000);
    printf("copy_substr(s1, 34, 10000): '%s'\n", str);
    free(str);
    
    str = copy_substr(s1, 34, 0);
    printf("copy_substr(s1, 34, 0): '%s'\n", str);
    free(str);
  }
  
  
  __("substr_count"); {
    printf("substr_count(s1, \"Vee\"): %ld\n", substr_count(s1, "Vee"));
    printf("substr_count(s1, \"Cator\"): %ld\n", substr_count(s1, "Cator"));
  }
  
  
  __("strcase"); {
    str = copy_str(s1);
    
    printf("strtolowwer(s1): '%s'\n", strtolower(&str));
    printf("strtoupper(s1): '%s'\n", strtoupper(&str));
    printf("lcfirst(s1): '%s'\n", lcfirst(&str));
    strtolower(&str);
    printf("ucfirst(s1): '%s'\n", ucfirst(&str));
    strtolower(&str);
    printf("ucwords(s1): '%s'\n", ucwords(&str));
    
    free(str);
  }
  
  
  __("trim"); {
    str = copy_str(" \t\v cator \r\n ");
    printf("ltrim(\" \\t\\v cator \\r\\n \"): '%s'\n", ltrim(&str));
    free(str);
    
    str = copy_str(" \t\v cator \r\n ");
    printf("rtrim(\" \\t\\v cator \\r\\n \"): '%s'\n", rtrim(&str));
    free(str);
    
    str = copy_str(" \t\v cator \r\n ");
    printf("trim(\" \\t\\v cator \\r\\n \"): '%s'\n", trim(&str));
    free(str);
  }
  
  
  __("repeat"); {
    str = copy_repeat("-=", 10);
    printf("copy_repeat(\"-=\", 10): '%s'\n", str);
    free(str);
    
    str = copy_strpad(s2, 20, "-=", STR_PAD_LEFT);
    printf("copy_strpad(s2, 20, \"-=\", STR_PAD_LEFT): '%s'\n", str);
    free(str);
    
    str = copy_strpad(s2, 20, "-=", STR_PAD_RIGHT);
    printf("copy_strpad(s2, 20, \"-=\", STR_PAD_RIGHT): '%s'\n", str);
    free(str);
    
    str = copy_strpad(s2, 20, "-=", STR_PAD_BOTH);
    printf("copy_strpad(s2, 20, \"-=\", STR_PAD_BOTH): '%s'\n", str);
    free(str);
  }
  
  
  __("replace"); {
    str = copy_str(s1);
    printf("strtr(&str, \"ctr\", \"CTR\"): '%s'\n", strtr(&str, "ctr", "CTR"));
    free(str);
    
    str = copy_str(s1);
    printf("copy_replace(\"Vee\", \"Wei++\", s1): '%s'\n", copy_replace("Vee", "Wei++", s1));
    free(str);
  }
  
  return 0;
}

