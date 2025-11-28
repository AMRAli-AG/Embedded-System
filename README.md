# CoreX - AI-Driven Digital Twin Framework

<div align="center">

<img width="288" height="128" alt="2-removebg-preview" src="https://github.com/user-attachments/assets/7a13f564-64aa-4f03-863d-eeb414e2a879" />


![Status](https://img.shields.io/badge/Status-In%20Development-yellow?style=for-the-badge)
![Phase](https://img.shields.io/badge/Phase-Research%20%26%20Planning-green?style=for-the-badge)

**AI-Driven Digital Twin Framework for Predictive Maintenance and Operational Optimization in Industrial Robotic Systems**

[Project Overview](#-project-overview) •
[Features](#-features) •
[Architecture](#-system-architecture) •
[Project Plan](#-complete-project-plan) •
[Team](#-team-structure) •
[Documentation](#-documentation)

</div>

---

## 📋 Project Overview

CoreX is an integrated framework combining **Artificial Intelligence** and **Digital Twin** technologies to enable predictive maintenance and operational optimization for industrial robotic systems. The system provides real-time monitoring, anomaly detection, and predictive analytics for KUKA robotic arms.

### 🎯 Key Objectives

- **Model Development**: Construct a high-fidelity digital twin reflecting ≥95% of real operational behavior
- **Predictive Intelligence**: AI models with ≥90% accuracy for anomaly detection and failure forecasting
- **Operational Insight**: Real-time dashboard reducing unplanned downtime by ≥30%
- **Validation Framework**: Black-Box validation maintaining ≤5% variance from physical system

---

## ✨ Features

### 🤖 AI & Machine Learning
- Real-time anomaly detection
- Remaining Useful Life (RUL) prediction
- Fault classification and identification
- Energy consumption optimization
- Mechanical stress reduction

### 🔄 Digital Twin
- High-fidelity virtual robot model
- Real-time synchronization with physical system
- Kinematic and dynamic simulation
- Stress and fatigue estimation
- Clean dataset generation for AI training

### 🔒 Security
- Network segmentation and isolation
- End-to-end data encryption (AES/TLS)
- SIEM implementation for monitoring
- Role-based access control (RBAC)
- Secure logging and audit trails

### 📊 Monitoring Dashboard
- Live robot telemetry visualization
- Anomaly detection indicators
- RUL estimates and alerts
- Performance trend graphs
- Real-time notifications

### ⚙️ Edge Deployment
- Low-resource optimization
- Jetson Nano / Raspberry Pi support
- ONNX runtime for inference
- Auto-boot AI services
- MQTT telemetry streaming

---

## 🏗 System Architecture
```
┌─────────────────────────────────────────────────────────────┐
│                     Physical Layer                           │
│  ┌──────────────┐         ┌─────────────────┐              │
│  │  KUKA Robot  │────────▶│  Black Box      │              │
│  │              │ Ethernet │  (MCU Module)   │              │
│  └──────────────┘         └─────────────────┘              │
└────────────────────────────────┬────────────────────────────┘
                                 │
┌────────────────────────────────▼────────────────────────────┐
│                   Edge Computing Layer                       │
│  ┌────────────────┐    ┌──────────────────┐                │
│  │  Data          │───▶│  AI Models       │                │
│  │  Acquisition   │    │  - Anomaly Det.  │                │
│  └────────────────┘    │  - RUL Pred.     │                │
│                        │  - Fault Class.  │                │
│                        └──────────────────┘                │
└────────────────────────────────┬────────────────────────────┘
                                 │
┌────────────────────────────────▼────────────────────────────┐
│                   Software Layer                             │
│  ┌────────────────┐    ┌──────────────────┐                │
│  │  Digital Twin  │◀──▶│  Dashboard       │                │
│  │  Simulation    │    │  (ThingsBoard)   │                │
│  └────────────────┘    └──────────────────┘                │
│                                                              │
│  ┌────────────────────────────────────────┐                │
│  │         Security Layer (SIEM)          │                │
│  └────────────────────────────────────────┘                │
└─────────────────────────────────────────────────────────────┘
```

---

## 📅 Complete Project Plan

### Timeline Overview
- **Total Duration**: 9.5 months (Oct 2025 - July 2026)
- **Total Phases**: 4
- **Teams**: Embedded Systems, AI/ML, Security

### Phase Summary

| Phase | Name | Duration | Period | Teams Involved |
|-------|------|----------|--------|----------------|
| **Phase 1** | Research & Planning | 2 months | Oct 1 - Dec 2, 2025 | All Teams |
| **Phase 2** | Design & Prototyping | 4.5 months | Dec 3, 2025 - Apr 14, 2026 | All Teams (Parallel) |
| **Phase 3** | Integration & Dashboard | 1.5 months | Apr 15 - May 26, 2026 | All Teams (Parallel) |
| **Phase 4** | Testing & Validation | 2 months | May 27 - July 21, 2026 | All Teams |

---

## 📆 Phase 1: Research & Planning
**Duration:** Oct 1 - Dec 2, 2025 (2 months)

| Milestone | Duration | Start Date | End Date | Deliverable |
|-----------|----------|------------|----------|-------------|
| Literature Review | 2 weeks | Oct 1, 2025 | Oct 14, 2025 | Research report on AI, Digital Twin, and predictive maintenance |
| Requirement Analysis | 2 weeks | Oct 15, 2025 | Oct 28, 2025 | System requirements document |
| System Architecture & Planning | 3 weeks | Oct 29, 2025 | Nov 18, 2025 | Detailed architecture diagram and technical specifications |
| Component Selection & Sourcing | 2 weeks | Nov 19, 2025 | Dec 2, 2025 | Bill of Materials (BOM) and procurement plan |

### Key Deliverables:
- ✅ Literature review report
- ✅ Requirements specification document
- ✅ System architecture design
- ✅ Component procurement list
- ✅ Project risk assessment

---

## 📆 Phase 2: Design & Prototyping
**Duration:** Dec 3, 2025 - Apr 14, 2026 (4.5 months)

### **Week 1-2: Dec 3 - Dec 16, 2025**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Data Acquisition from KUKA Robot | Embedded | Ethernet tap, Wireshark, KUKA frames | Robot telemetry dataset |
| Problem Definition & Data Requirements | AI | Robot tasks, failure modes | Problem statement |
| Port Security Hardening | Security | Network architecture | Secured ports |

### **Week 3-5: Dec 17, 2025 - Jan 6, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Low-Resource Ubuntu VM Setup | Embedded | VM, Ubuntu ISO | Test environment |
| Data Preprocessing & Features | AI | Raw dataset | Clean dataset |
| Data Encryption on Ethernet | Security | AES/TLS libs | Encrypted packets |

### **Week 6-8: Dec 31, 2025 - Jan 27, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Run AI Model on Low-Resource VM | Embedded | AI model, ONNX runtime | Model inference |
| Anomaly Detection Model | AI | Anomaly data | Trained model |
| SIEM Training + SW Security | Security | SIEM logs | Security monitoring skills |

### **Week 9-11: Jan 21 - Feb 10, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Deploy Model on Jetson/Pi | Embedded | Edge devices, drivers | Hardware benchmarks |
| Fault Identification (Optional) | AI | Fault labels | Fault classifier |
| SIEM Implementation | Security | Logs from all teams | SIEM dashboard |

### **Week 12-14: Feb 11 - Mar 3, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| ThingsBoard Dashboard | Embedded | MQTT/HTTP | Live robot dashboard |
| RUL Model Development | AI | Sequence data | RUL model |

### **Week 15-16: Mar 4 - Mar 17, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Auto-Boot AI Service | Embedded | systemd scripts | Auto-run AI at startup |
| Model Evaluation & Selection | AI | Metrics | Best model |

### **Week 17-18: Mar 18 - Mar 31, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Optimization (Energy/Stress) | AI | Digital Twin | Optimized trajectories |

### **Week 19: Apr 1 - Apr 14, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| AI/DT Integration | AI | APIs, DT engine | Integrated AI system |

### Key Deliverables:
- ✅ Functional Black Box module for data acquisition
- ✅ Trained AI models (Anomaly Detection, Fault Identification, RUL Prediction)
- ✅ Security implementation (Encryption, SIEM)
- ✅ Edge device deployment (Jetson/Raspberry Pi)
- ✅ ThingsBoard monitoring dashboard
- ✅ Digital Twin integrated with AI

---

## 📆 Phase 3: Integration & Dashboard
**Duration:** Apr 15 - May 26, 2026 (1.5 months)

### **Week 1-2: Apr 15 - Apr 28, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Connect Edge Devices to AI System | Embedded | Hardware + models | Real-time inference |
| AI–Dashboard Connection | AI | Dashboard API | Live anomaly + RUL |
| Encryption & Access Control Review | Security | Network config | Secured robot network |

### **Week 3-4: Apr 29 - May 12, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Telemetry Streaming (MQTT Loop) | Embedded | MQTT Broker | Data stream |
| Digital Twin Sync with Real Robot | AI | Robot data | Synced DT |
| SIEM Dashboard Finalization | Security | SIEM logs | Real-time alerts |

### **Week 5-6: May 13 - May 26, 2026**
| Milestone | Team | Requirements | Output |
|-----------|------|--------------|--------|
| Full Embedded Integration Testing | Embedded | All team modules | Stable pipeline |
| Full AI Pipeline Validation | AI | All components | Production-ready AI |
| Full Security Validation / Pen-Test | Security | System modules | Final security report |

### Key Deliverables:
- ✅ Fully integrated system (Hardware + Software + AI)
- ✅ Real-time telemetry streaming via MQTT
- ✅ Synchronized Digital Twin with physical robot
- ✅ Complete dashboard with live monitoring
- ✅ Security validation and penetration testing report

---

## 📆 Phase 4: Testing & Validation
**Duration:** May 27 - July 21, 2026 (2 months)

| Milestone | Duration | Start Date | End Date | Deliverable |
|-----------|----------|------------|----------|-------------|
| Controlled Testing | 2 weeks | May 27, 2026 | June 9, 2026 | Test results and performance metrics |
| Performance Optimization | 2 weeks | June 10, 2026 | June 23, 2026 | Optimized system with improved efficiency |
| Real-World Simulation | 2 weeks | June 24, 2026 | July 7, 2026 | Real-world validation report |
| Final Report & Presentation | 2 weeks | July 8, 2026 | July 21, 2026 | Final project report and defense presentation |

### Key Deliverables:
- ✅ Comprehensive testing report
- ✅ Performance optimization documentation
- ✅ Real-world validation results
- ✅ Final project report
- ✅ Project presentation and defense materials

---

## 📊 Gantt Chart Overview
```
Phase 1: Research & Planning
██████████ (Oct-Dec 2025)

Phase 2: Design & Prototyping
          ████████████████████████ (Dec 2025 - Apr 2026)
          
          Embedded: ████████████████████████
          AI:       ████████████████████████
          Security: ████████████████████████

Phase 3: Integration & Dashboard
                                  ████████ (Apr-May 2026)
                                  
                                  Embedded: ████████
                                  AI:       ████████
                                  Security: ████████

Phase 4: Testing & Validation
                                          ████████████ (May-Jul 2026)
```

---

## 📈 Critical Path & Dependencies

### Sequential Dependencies:
1. **Phase 1 → Phase 2**: Requirements and architecture must be finalized before development
2. **Data Acquisition → AI Training**: Clean data is prerequisite for model training
3. **AI Models → Dashboard**: Dashboard displays AI outputs, requires models first
4. **Integration → Testing**: Complete system required for validation

### Parallel Work Opportunities:
- ✅ **Phase 2**: All three teams (Embedded, AI, Security) work simultaneously
- ✅ **Phase 3**: Integration happens in parallel across all teams
- ✅ Security implementation runs parallel to AI development throughout

---

## 👥 Team Structure

### 🔧 Embedded Systems Team
**Responsibilities**:
- Data acquisition from KUKA robot via Ethernet (Black Box Module)
- Edge device setup and configuration
- Model deployment on resource-constrained hardware
- Dashboard development and telemetry streaming
- System integration and testing

**Tech Stack**: Linux, Python, MQTT, Docker, Edge Computing, ONNX Runtime

**Key Milestones**: 8 major milestones across Phases 2-3

---

### 🧠 AI/Machine Learning Team
**Responsibilities**:
- Digital Twin development and simulation
- AI model training (Anomaly Detection, RUL, Fault Classification)
- Model optimization and evaluation
- Operational optimization algorithms
- AI-Dashboard integration

**Tech Stack**: Python, TensorFlow/PyTorch, ONNX, Scikit-learn, Digital Twin frameworks

**Key Milestones**: 9 major milestones across Phases 2-3

---

### 🔒 Security Team
**Responsibilities**:
- Network security architecture
- Data encryption implementation (AES/TLS)
- SIEM setup and monitoring
- Access control and authentication
- Security auditing and penetration testing

**Tech Stack**: Network Security, Encryption (AES/TLS), SIEM, Firewalls, Security Auditing

**Key Milestones**: 7 major milestones across Phases 2-3

---

## 🛠 Technology Stack

### Hardware
- **Robot**: KUKA Industrial Robot
- **Data Acquisition**: Black Box Module (Microcontroller-based)
- **Edge Computing**: Jetson Nano / Raspberry Pi
- **Network**: Ethernet Infrastructure

### Software & Frameworks
- **Programming Languages**: Python, C/C++, Bash
- **AI/ML**: TensorFlow, PyTorch, Scikit-learn, ONNX Runtime
- **Communication**: MQTT, HTTP/REST APIs
- **Dashboard**: ThingsBoard
- **Security**: AES/TLS Encryption, SIEM Tools
- **Virtualization**: Docker, Ubuntu VM
- **Version Control**: Git, GitHub
- **CI/CD**: GitHub Actions

---

## 📊 Success Metrics

### Phase 1 Success Criteria
- ✅ Complete system architecture approved by all stakeholders
- ✅ All hardware/software components procured
- ✅ Requirements document signed off
- ✅ Risk assessment completed

### Phase 2 Success Criteria
- ✅ AI models achieve ≥90% accuracy in anomaly detection
- ✅ Edge devices running AI inference successfully
- ✅ Dashboard displaying real-time data
- ✅ All security measures implemented and tested
- ✅ Digital Twin accuracy ≥95%

### Phase 3 Success Criteria
- ✅ All systems integrated and communicating properly
- ✅ Digital Twin synchronized with real robot (≤5% variance)
- ✅ Zero critical security vulnerabilities found
- ✅ System stable for 72+ hours continuous operation
- ✅ Real-time alerts functioning correctly

### Phase 4 Success Criteria
- ✅ 30% reduction in unplanned downtime demonstrated
- ✅ AI predictions within 5% variance of actual behavior
- ✅ System passes real-world validation tests
- ✅ Final documentation complete and approved
- ✅ Successful project defense

---

## 🎯 Risk Management

### Phase 1 Risks
| Risk | Impact | Mitigation |
|------|--------|------------|
| Incomplete requirements | High | Extra week buffer in planning phase |
| Component unavailability | Medium | Alternative suppliers identified |

### Phase 2 Risks
| Risk | Impact | Mitigation |
|------|--------|------------|
| Data quality issues | High | Multiple validation checkpoints |
| Model underperformance | High | 2-week evaluation milestone |
| Hardware compatibility | Medium | Early testing on VM before deployment |

### Phase 3 Risks
| Risk | Impact | Mitigation |
|------|--------|------------|
| Integration failures | High | 2-week dedicated testing period |
| Security vulnerabilities | Critical | Penetration testing scheduled |
| Synchronization issues | Medium | Incremental integration approach |

### Phase 4 Risks
| Risk | Impact | Mitigation |
|------|--------|------------|
| Failed validation | High | 2-week optimization buffer included |
| Performance degradation | Medium | Continuous monitoring during testing |

---

## 📖 Documentation

- [Project Proposal](docs/proposal.pdf)
- [System Architecture](docs/architecture.md)
- [Timeline Documentation](docs/timeline.md)
- [API Documentation](docs/api.md)
- [User Guide](docs/user-guide.md)
- [Security Guidelines](docs/security.md)
- [Team Handbook](docs/team-handbook.md)

---

## 🚀 Getting Started

### Prerequisites
```bash
# Python 3.8+
python --version

# Docker
docker --version

# Git
git --version
```

### Installation
```bash
# Clone the repository
git clone https://github.com/corex/digital-twin-framework.git

# Navigate to project directory
cd digital-twin-framework

# Install dependencies
pip install -r requirements.txt

# Run setup script
./setup.sh
```

### Quick Start
```bash
# Start the Black Box data acquisition
./scripts/start_blackbox.sh

# Launch Digital Twin simulation
python src/digital_twin/main.py

# Start AI inference
python src/ai/inference.py

# Launch dashboard
docker-compose up dashboard
```

---

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🤝 Contributing

Contributions are welcome! Please read our [Contributing Guidelines](CONTRIBUTING.md) before submitting pull requests.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📧 Contact

**CoreX Team**
- 📧 Email: corex@project.com
- 🌐 Website: [corex-project.com](https://corex-project.com)
- 💼 LinkedIn: [CoreX Project](https://linkedin.com/company/corex)
- 🐦 Twitter: [@CoreXProject](https://twitter.com/corexproject)

---

## 📈 Project Status

![Progress](https://img.shields.io/badge/Progress-15%25-yellow?style=for-the-badge)
![Phase](https://img.shields.io/badge/Current%20Phase-Phase%201-green?style=for-the-badge)
![Next Milestone](https://img.shields.io/badge/Next%20Milestone-Architecture%20Design-blue?style=for-the-badge)

### Current Sprint (Week of Nov 28, 2025)
- 🔄 Finalizing system architecture design
- 📚 Completing literature review
- 🛒 Sourcing components

### Upcoming Milestones
- **Dec 2, 2025**: Complete Phase 1
- **Dec 3, 2025**: Begin Phase 2 - Data Acquisition
- **Dec 16, 2025**: First data collection from KUKA robot

**Last Updated**: November 28, 2025

---

## 🏆 Acknowledgments

- KUKA Robotics for technical specifications
- Industry 4.0 research community
- Open-source AI/ML community
- Our academic advisors and mentors

---

<div align="center">

**CoreX © 2025** | Building the Future of Industrial Automation

[![GitHub Stars](https://img.shields.io/github/stars/corex/digital-twin-framework?style=social)](https://github.com/corex/digital-twin-framework)
[![GitHub Forks](https://img.shields.io/github/forks/corex/digital-twin-framework?style=social)](https://github.com/corex/digital-twin-framework)
[![GitHub Issues](https://img.shields.io/github/issues/corex/digital-twin-framework?style=social)](https://github.com/corex/digital-twin-framework/issues)

[⬆ Back to Top](#corex---ai-driven-digital-twin-framework)

</div>
