#add_executable(testbatal testbatal.c)
#target_link_libraries(testbatal LINK_PUBLIC grille batals display)

add_executable(test_init test_init.c)
target_link_libraries(test_init LINK_PUBLIC init)

add_executable(test_link test_link.c)
target_link_libraries(test_link LINK_PUBLIC interface link)

add_executable(test_winner test_winner.c)
target_link_libraries(test_winner LINK_PUBLIC interface link init winner)

add_executable(test_play_turn test_play_turn.c)
target_link_libraries(test_play_turn LINK_PUBLIC interface link init play cards)



add_executable(test_AI_0 test_AI_0.c)
target_link_libraries(test_AI_0 LINK_PUBLIC link cards play)

add_executable(test_AI_1 test_AI_1.c)
target_link_libraries(test_AI_1 LINK_PUBLIC link cards play)


#add_test(test_init test_init)
add_test(test_link test_link)
#add_test(test_winner test_winner)
#add_test(test_play_turn test_play_turn)
add_test(test_AI_0 test_AI_0)
add_test(test_AI_1 test_AI_1)
