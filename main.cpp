#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Student {
    double attendance;
    double studyHours;
    double previousMarks;
    double assignments;
    string label;
};

struct Neighbor {
    double distance;
    string label;
    int index;
};

static double normalize(double value, double minValue, double maxValue) {
    if (maxValue == minValue) {
        return 0.0;
    }
    return (value - minValue) / (maxValue - minValue);
}

static vector<double> features(const Student& s) {
    return {s.attendance, s.studyHours, s.previousMarks, s.assignments};
}

static void getFeatureBounds(const vector<Student>& training,
                             vector<double>& minValues,
                             vector<double>& maxValues) {
    minValues.assign(4, numeric_limits<double>::max());
    maxValues.assign(4, numeric_limits<double>::lowest());

    for (const auto& student : training) {
        const auto values = features(student);
        for (size_t i = 0; i < values.size(); ++i) {
            minValues[i] = min(minValues[i], values[i]);
            maxValues[i] = max(maxValues[i], values[i]);
        }
    }
}

static double euclideanDistance(const Student& a,
                                const Student& b,
                                const vector<double>& minValues,
                                const vector<double>& maxValues) {
    const auto aFeatures = features(a);
    const auto bFeatures = features(b);

    double sum = 0.0;
    for (size_t i = 0; i < aFeatures.size(); ++i) {
        const double aNormalized = normalize(aFeatures[i], minValues[i], maxValues[i]);
        const double bNormalized = normalize(bFeatures[i], minValues[i], maxValues[i]);
        const double difference = aNormalized - bNormalized;
        sum += difference * difference;
    }

    return sqrt(sum);
}

static string predictKNN(const vector<Student>& training,
                         const Student& query,
                         int k) {
    vector<double> minValues;
    vector<double> maxValues;
    getFeatureBounds(training, minValues, maxValues);

    vector<Neighbor> neighbors;
    neighbors.reserve(training.size());

    for (size_t i = 0; i < training.size(); ++i) {
        neighbors.push_back({
            euclideanDistance(training[i], query, minValues, maxValues),
            training[i].label,
            static_cast<int>(i)
        });
    }

    sort(neighbors.begin(), neighbors.end(),
         [](const Neighbor& a, const Neighbor& b) {
             return a.distance < b.distance;
         });

    k = max(1, min(k, static_cast<int>(neighbors.size())));

    map<string, int> votes;
    cout << "\nNearest neighbours:\n";
    for (int i = 0; i < k; ++i) {
        ++votes[neighbors[i].label];
        cout << i + 1 << ". " << left << setw(7) << neighbors[i].label
             << " distance=" << fixed << setprecision(3)
             << neighbors[i].distance << '\n';
    }

    string prediction;
    int bestVotes = -1;

    for (const auto& entry : votes) {
        if (entry.second > bestVotes) {
            bestVotes = entry.second;
            prediction = entry.first;
        }
    }

    return prediction;
}

static double readValue(const string& prompt, double low, double high) {
    while (true) {
        cout << prompt;
        double value;

        if (cin >> value && value >= low && value <= high) {
            return value;
        }

        cout << "Invalid value. Enter a number between "
             << low << " and " << high << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static void printDataset(const vector<Student>& training) {
    cout << "\nTraining Dataset\n";
    cout << left
         << setw(15) << "Attendance"
         << setw(14) << "Study Hours"
         << setw(15) << "Prev. Marks"
         << setw(16) << "Assignments"
         << "Class\n";

    cout << string(70, '-') << '\n';

    cout << fixed << setprecision(1);
    for (const auto& s : training) {
        cout << setw(15) << s.attendance
             << setw(14) << s.studyHours
             << setw(15) << s.previousMarks
             << setw(16) << s.assignments
             << s.label << '\n';
    }
}

int main() {
    // Small labelled dataset used for this educational project.
    const vector<Student> training = {
        {45, 1.0, 42, 50, "Low"},
        {52, 1.5, 48, 55, "Low"},
        {58, 2.0, 54, 60, "Low"},
        {65, 2.5, 62, 68, "Medium"},
        {70, 3.0, 67, 72, "Medium"},
        {74, 3.5, 71, 76, "Medium"},
        {82, 4.5, 78, 85, "High"},
        {88, 5.5, 84, 90, "High"},
        {94, 6.5, 91, 96, "High"}
    };

    cout << "==============================================\n";
    cout << "   AI-Based Student Performance Predictor\n";
    cout << "   C++17 | k-Nearest Neighbours (k-NN)\n";
    cout << "==============================================\n";

    char showData;
    cout << "Show training dataset? (y/n): ";
    cin >> showData;
    if (showData == 'y' || showData == 'Y') {
        printDataset(training);
    }

    Student query{};
    cout << "\nEnter student details:\n";
    query.attendance = readValue("Attendance (0-100): ", 0, 100);
    query.studyHours = readValue("Daily study hours (0-12): ", 0, 12);
    query.previousMarks = readValue("Previous marks (0-100): ", 0, 100);
    query.assignments = readValue("Assignments completed % (0-100): ", 0, 100);

    constexpr int k = 3;
    const string prediction = predictKNN(training, query, k);

    cout << "\nPredicted Performance Category: " << prediction << '\n';

    if (prediction == "Low") {
        cout << "Suggestion: improve consistency and seek academic support.\n";
    } else if (prediction == "Medium") {
        cout << "Suggestion: maintain progress and strengthen weak topics.\n";
    } else {
        cout << "Suggestion: maintain current habits and attempt advanced work.\n";
    }

    cout << "\nNote: This is an educational prototype, not an official academic decision system.\n";
    return 0;
}
