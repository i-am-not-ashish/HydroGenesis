import numpy as np
import joblib
from sklearn.ensemble import RandomForestRegressor

def convert_model_to_cpp(model, model_name):
    """Converts a scikit-learn model to C++ compatible arrays"""
    estimators = model.estimators_
    
    # Model parameters
    n_estimators = model.n_estimators
    n_features = model.n_features_in_
    n_classes = 1  # Regression
    
    # Header file content
    header_content = f"""#ifndef {model_name.upper()}_H
#define {model_name.upper()}_H

#include <array>

const int {model_name}_N_TREES = {n_estimators};
const int {model_name}_N_FEATURES = {n_features};
const int {model_name}_N_CLASSES = {n_classes};

"""

    # Tree structures
    tree_declarations = ""
    tree_definitions = ""
    
    for i, tree in enumerate(estimators):
        tree = tree.tree_
        
        # Tree structure
        n_nodes = tree.node_count
        children_left = tree.children_left
        children_right = tree.children_right
        feature = tree.feature
        threshold = tree.threshold
        value = tree.value.reshape(tree.value.shape[0], 1)
        
        # Add to header
        tree_declarations += f"extern const std::array<int, {n_nodes}> {model_name}_tree{i}_children_left;\n"
        tree_declarations += f"extern const std::array<int, {n_nodes}> {model_name}_tree{i}_children_right;\n"
        tree_declarations += f"extern const std::array<int, {n_nodes}> {model_name}_tree{i}_feature;\n"
        tree_declarations += f"extern const std::array<float, {n_nodes}> {model_name}_tree{i}_threshold;\n"
        tree_declarations += f"extern const std::array<float, {n_nodes}> {model_name}_tree{i}_value;\n\n"
        
        tree_definitions += f"const std::array<int, {n_nodes}> {model_name}_tree{i}_children_left = {{{', '.join(map(str, children_left))}}};\n"
        tree_definitions += f"const std::array<int, {n_nodes}> {model_name}_tree{i}_children_right = {{{', '.join(map(str, children_right))}}};\n"
        tree_definitions += f"const std::array<int, {n_nodes}> {model_name}_tree{i}_feature = {{{', '.join(map(str, feature))}}};\n"
        tree_definitions += f"const std::array<float, {n_nodes}> {model_name}_tree{i}_threshold = {{{', '.join(map(str, threshold))}}};\n"
        tree_definitions += f"const std::array<float, {n_nodes}> {model_name}_tree{i}_value = {{{', '.join(map(str, value.flatten()))}}};\n\n"
    
    header_content += tree_declarations
    header_content += "#endif\n"
    
    # Save header file
    with open(f"{model_name}_model.h", "w") as f:
        f.write(header_content)
    
    # Save implementation file
    with open(f"{model_name}_model.cpp", "w") as f:
        f.write(tree_definitions)
    
    print(f"Model converted to C++ and saved as {model_name}_model.h and {model_name}_model.cpp")

if __name__ == "__main__":
    # Convert both models
    moisture_model = joblib.load('moisture_model.joblib')
    water_level_model = joblib.load('water_level_model.joblib')
    
    convert_model_to_cpp(moisture_model, "moisture")
    convert_model_to_cpp(water_level_model, "water_level")