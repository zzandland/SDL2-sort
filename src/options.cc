#include "options.h"

#include <string>
#include <string_view>

namespace {
    Algorithm StringToAlgorithm(const std::string& s) {
        if (s == "bubble") return Algorithm::kBubbleSort;
        if (s == "insertion") return Algorithm::kInsertionSort;
        if (s == "selection") return Algorithm::kSelectionSort;
        if (s == "quick") return Algorithm::kQuickSort;
        if (s == "merge") return Algorithm::kMergeSort;
        if (s == "heap") return Algorithm::kHeapSort;
        return Algorithm::kBubbleSort;
    }

    DiagramType StringToDiagramType(const std::string& s) {
        if (s == "scatter") return DiagramType::kScatterPlot;
        if (s == "histogram") return DiagramType::kHistogram;
        return DiagramType::kHistogram;
    }
}

ProgramOptions ParseCommandLine(int argc, char* argv[]) {
    ProgramOptions options;
    std::string algorithm_str = "bubble";
    std::string diagram_str = "histogram";

    for (int i = 1; i < argc; ++i) {
        std::string_view arg(argv[i]);
        if ((arg == "-a" || arg == "--algorithm") && i + 1 < argc) {
            algorithm_str = argv[++i];
        } else if ((arg == "-v" || arg == "--visualization") && i + 1 < argc) {
            diagram_str = argv[++i];
        }
    }

    options.algorithm = StringToAlgorithm(algorithm_str);
    options.diagram = StringToDiagramType(diagram_str);

    return options;
} 