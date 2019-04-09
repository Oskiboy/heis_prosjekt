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
                dir('elevator_simulator') {
                    deleteDir()
                }
                sh """
                mkdir test_logs logs
                echo "Logs Initialized" >> test_logs/test.log
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
        stage('Build simulator') {
            steps {
                sh '''
                cd elevator_simulator
                ./build.sh
                ./build_wrapper.sh
                '''
            }
        }
        stage('UnitTests') {
            steps {
                sh 'mv elevator_simulator/libelev_wrapper.a tests/'
                sh 'echo "Running Unit Tests:"'
                sh 'make tests'
                sh 'echo "Tests built successfully"'
                sh '''
                echo "Running server..."
                ./elevator_simulator/build/sim_server > /dev/null 2>&1 &
                export SERVER_PID=$!
                echo $SERVER_PID
                sleep 1
                ps a >> test_logs/test.log
                make run_tests >> test_logs/test.log
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
            archiveArtifacts artifacts: "test_logs/*.log, build/heis, logs/*.log"
            sh '''
            ls
            echo "Starting clean"
            make clean
            rm -rf build/ test_logs/ logs/ tests/build/
            '''
        }
    }
}
