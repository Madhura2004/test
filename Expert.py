class AdvancedMedicalExpertSystem:
    def __init__(self):
        # Expanded disease dictionary with more diseases and symptoms
        self.diseases = {
            "Common Cold": {
                "symptoms": {
                    "sneezing": 3,
                    "runny nose": 3,
                    "cough": 2,
                    "sore throat": 2,
                    "headache": 1
                },
                "advice": "Take rest and stay hydrated. Use nasal sprays.",
                "urgency": "Low"
            },
            "Flu": {
                "symptoms": {
                    "fever": 4,
                    "cough": 3,
                    "fatigue": 3,
                    "body ache": 3,
                    "chills": 2,
                    "sore throat": 2
                },
                "advice": "Rest, drink fluids, and take antipyretics.",
                "urgency": "Medium"
            },
            "COVID-19": {
                "symptoms": {
                    "fever": 4,
                    "dry cough": 4,
                    "loss of smell": 5,
                    "difficulty breathing": 5,
                    "fatigue": 3,
                    "headache": 2,
                    "chills": 2
                },
                "advice": "Isolate and consult a healthcare provider immediately.",
                "urgency": "High"
            },
            "Food Poisoning": {
                "symptoms": {
                    "vomiting": 4,
                    "diarrhea": 4,
                    "stomach pain": 3,
                    "fever": 2,
                    "nausea": 3
                },
                "advice": "Take ORS, stay hydrated, and see a doctor if severe.",
                "urgency": "Medium"
            },
            "Strep Throat": {
                "symptoms": {
                    "sore throat": 4,
                    "fever": 4,
                    "red rash": 3,
                    "headache": 2
                },
                "advice": "Consult a doctor for antibiotics.",
                "urgency": "Medium"
            },
            "Pneumonia": {
                "symptoms": {
                    "cough": 4,
                    "difficulty breathing": 5,
                    "fever": 4,
                    "fatigue": 3,
                    "chest pain": 4
                },
                "advice": "Seek medical help immediately.",
                "urgency": "High"
            },
            "Migraine": {
                "symptoms": {
                    "headache": 5,
                    "nausea": 4,
                    "sensitivity to light": 3,
                    "vomiting": 3
                },
                "advice": "Rest in a dark room and consider pain relief medication.",
                "urgency": "Medium"
            }
        }

    def get_user_symptoms(self):
        print("\n--- Advanced Symptom Checker ---")
        print("Enter your symptoms (comma-separated):")
        user_input = input("Symptoms: ").lower()
        return set(sym.strip() for sym in user_input.split(','))

    def diagnose(self, user_symptoms):
        diagnosis_results = []

        for disease, info in self.diseases.items():
            symptoms = info["symptoms"]
            matched_weight = sum(weight for sym, weight in symptoms.items() if sym in user_symptoms)
            total_weight = sum(symptoms.values())
            confidence = matched_weight / total_weight

            # Adjust confidence and allow diagnosis if confidence is more than 0.4
            if confidence >= 0.4:
                diagnosis_results.append({
                    "disease": disease,
                    "confidence": round(confidence * 100, 2),
                    "advice": info["advice"],
                    "urgency": info["urgency"]
                })

        if diagnosis_results:
            diagnosis_results.sort(key=lambda x: x["confidence"], reverse=True)
            print("\n✅ Diagnosis Result (Sorted by Confidence):\n")
            for result in diagnosis_results:
                print(f"🔹 Disease: {result['disease']}")
                print(f"   - Confidence: {result['confidence']}%")  
                print(f"   - Urgency: {result['urgency']}")
                print(f"   - Advice: {result['advice']}\n")
        else:
            print("\n❗ No matching disease found with sufficient confidence. Please consult a doctor.")

    def run(self):
        user_symptoms = self.get_user_symptoms()
        self.diagnose(user_symptoms)

# Run it
if __name__ == "__main__":
    system = AdvancedMedicalExpertSystem()
    system.run()


# fever, sore throat, headache
# headache, nausea, vomiting
# fever, cough, body ache, fatigue
# sore throat, fever, red rash, headache