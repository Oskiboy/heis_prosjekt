pipeline {
    agent { 
        dockerfile {
            filename 'Dockerfile'
            dir 'Docker'
        }
    }
    stages {
        stage('Initialization') {
            steps {
                dir('ElevatorSimulator') {
                    deleteDir()
                }
                sh """
                mkdir logs
                echo "Logs Initialized" >> logs/test.log
                git submodule init
                git submodule update
                """
            }
        }
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                make

                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('Get Simulator') {
            steps {
                copyArtifacts(projectName: 'ElevatorSimulator', excludes: '*.log', target: ElevatorSimulator, flatten: true)
            }
        }
        stage('UnitTests') {
            steps {
                sh 'mv ElevatorSimulator/libelev_wrapper.a tests/'
                sh 'echo "Running Unit Tests:"'
                sh 'make tests'
                sh 'echo "Tests built successfully"'
                sh '''
                echo "Running server..."
                ./ElevatorSimulator/sim_server &
                export SERVER_PID=$!
                make run_tests >> logs/test.log
                echo "Tests finished, killing server..."
                kill $SERVER_PID
                ''' 
            }
        }
    }
    post {
        success {
            sh '''
            echo "Build passed!"
            '''
        }
        failure {
            sh '''
            echo "Build failed!"
            '''
        }
        always {
            archiveArtifacts artifacts: "logs/*.log, build/heis"
            sh '''
            ls
            echo "Starting clean"
            make clean
            rm -rf build/ logs/
            '''
        }
    }
}
