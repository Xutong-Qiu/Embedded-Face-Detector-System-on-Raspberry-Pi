
SET(source_list
        actors/classifier.cpp
        actors/read_config.cpp
        actors/result_write.cpp
        actors/txt_img_read.cpp
	graph/graph.cpp
        utils/utils.cpp
        utils/strongC.cpp
	utils/WeakClassifier.cpp
        )

ADD_LIBRARY(team1_src ${source_list})
INSTALL(TARGETS team1_src DESTINATION $ENV{UXTMP})