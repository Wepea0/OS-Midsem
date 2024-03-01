 Test for update a tlb entry which already exists

 for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d-", TLB[i][j]);
            
        }
        printf("\n");
    }

    int process_index = entry_exists(2);
    update_tlb_entry(process_index);

    for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d-", TLB[i][j]);
            
        }
        printf("\n");
    }

    printf("\n");


    process_index = entry_exists(1);
    update_tlb_entry(process_index);
    
    printf("\n");

    for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d-", TLB[i][j]);
            
        }
        printf("\n");
    }



        ((((((((((((((((****************************))))))))))))))))


        Add to tlb exists 

        for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            TLB[i][j] = i;
            
        }
    }

    for(int i = 0; i < sizeof(TLB[0]); i++){
        TLB[2][0] = -1;
    }

    printf("\n");

    print_tlb();

    int tlb_index = space_exists();
    int test_ptr_int = ptr_to_integer(test_ptr);
    add_to_tlb_space_exists(tlb_index, 2, test_ptr_int);

    printf("\n");

    print_tlb();